/**
\file   VlcStatus.cpp
\author Elliot Goodrich

NowDisplaying - a program to display what music is currently playing.

Copyright (C) 2013 Elliot Goodrich

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "VlcStatus.hpp"

#include <QAuthenticator>
#include <QByteArray>
#include <QMutexLocker>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QScopedPointer>
#include <QXmlAttributes>
#include <QXmlDefaultHandler>
#include <QXmlInputSource>
#include <QXmlSimpleReader>

namespace {

/** Custom deleter for Qt smart pointers. */
struct DeleteLater {
	/** Delete the object later rather than now. */
	static void cleanup(QObject* ptr) {
		ptr->deleteLater();
	}
};

class VlcXmlContentHandler : public QXmlDefaultHandler {
public:
	VlcXmlContentHandler()
	: m_in_information{false}
	, m_write_to_me{nullptr} {
	}

	bool characters(const QString& ch) override {
		if(m_write_to_me) {
			*m_write_to_me = ch;
			m_write_to_me = nullptr;
		}
		return true;
	}

	bool endElement(const QString& /*namespaceURI*/, const QString& localName,
	                const QString& /*qName*/) override {
		if(localName == "information") {
			m_in_information = false;
		}
		return true;
	}

	bool startElement(const QString& /*namespaceURI*/, const QString& localName,
	                  const QString& /*qName*/, const QXmlAttributes& atts) override {
		if(m_in_information) {
			if(localName == "info") {
				auto index = atts.index("name");
				if(index != -1) {
					QString const name = atts.value(index);
					if(name == "title") {
						m_write_to_me = &m_title;
					} else if(name == "artist") {
						m_write_to_me = &m_artist;
					} else if(name == "album") {
						m_write_to_me = &m_album;
					} else if(name == "description") {
						m_write_to_me = &m_copyright;
					} else if(name == "artwork_url") {
						m_write_to_me = &m_album_path;
					} else {
						m_write_to_me = nullptr;
					}
				}
			}
		} else {
			if(localName == "information") {
				m_in_information = true;
			}
		}
		return true;
	}

	QString title() const {
		return m_title;
	}

	QString artist() const {
		return m_artist;
	}

	QString album() const {
		return m_album;
	}

	QString copyright() const {
		return m_copyright;
	}

	QString album_path() const {
		return m_album_path;
	}

private:
	bool m_in_information;
	QString* m_write_to_me;
	QString m_title, m_artist, m_album, m_copyright, m_album_path;
};

}

namespace nd {

/** Create an object to get the status of a VLC application through it's web interface. */
VlcStatus::VlcStatus(QUrl vlc_address, QString user, QString password)
: m_url{std::move(vlc_address)}
, m_user{std::move(user)}
, m_password{std::move(password)} {
	connect(&m_manager, &QNetworkAccessManager::finished, this, &VlcStatus::process_reply);
	connect(&m_manager, &QNetworkAccessManager::authenticationRequired,
	        this, &VlcStatus::authenticate);
}

/** Change the connection details for the VLC web interface. */
void VlcStatus::change_details(QUrl vlc_address, QString user, QString password) {
	m_url = std::move(vlc_address);
	m_user = std::move(user);
	m_password = std::move(password);
}

/** Update the status of VLC (asynchronous). */
void VlcStatus::update() {
	m_manager.get(QNetworkRequest{m_url});
}

/** Get the address that we are trying to connect to. */
QUrl const& VlcStatus::address() const {
	return m_url;
}

/** Get the username for the HTTP authentication. */
QString const& VlcStatus::user() const {
	return m_user;
}

/** Get the password for the HTTP authentication. */
QString const& VlcStatus::password() const {
	return m_password;
}

/** Get the name of the track playing. */
QString VlcStatus::title() const {
	QMutexLocker lock(&m_mutex);
	return m_title;
}

/** Get the artist of the track playing. */
QString VlcStatus::artist() const {
	QMutexLocker lock(&m_mutex);
	return m_artist;
}

/** Get the album of the track playing. */
QString VlcStatus::album() const {
	QMutexLocker lock(&m_mutex);
	return m_album;
}

/** Get the copyright of the track playing. */
QString VlcStatus::copyright() const {
	QMutexLocker lock(&m_mutex);
	return m_copyright;
}

/** Get the album art of the track playing. */
QFileInfo VlcStatus::album_art() const {
	QMutexLocker lock(&m_mutex);
	return m_album_art;
}

/** Process the update from status.xml. */
void VlcStatus::process_reply(QNetworkReply* reply) {
	// We own this pointer so must delete it, but according to Qt docs we can't delete it in
	// the slot function so we must call delete later on it.
	QScopedPointer<QNetworkReply, DeleteLater> scope_guard{reply};

	VlcXmlContentHandler handler;
	QXmlSimpleReader xml_reader;

	xml_reader.setContentHandler(&handler);
	QXmlInputSource network_source{reply};

	if(xml_reader.parse(network_source)) {
		/// \todo Figure out why there is a deadlock when the mutex is locked here
		//QMutexLocker lock(&m_mutex);
		{
			m_title     = handler.title();
			m_artist    = handler.artist();
			m_album     = handler.album();
			m_copyright = handler.copyright();
			auto raw_path = QUrl::fromPercentEncoding(handler.album_path().toUtf8());
			raw_path.replace("file:///", "");
			m_album_art = raw_path;
		}
	} else {
		m_title     = "";
		m_artist    = "";
		m_album     = "";
		m_copyright = "";
	}
	emit updated();
}

void VlcStatus::authenticate(QNetworkReply* /*reply*/, QAuthenticator* authenticator) const {
	authenticator->setUser(m_user);
	authenticator->setPassword(m_password);
}

}
