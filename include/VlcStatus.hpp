#ifndef INCLUDE_GUARD_5480A701_58BA_4C31_80F9_821763CBD22F
#define INCLUDE_GUARD_5480A701_58BA_4C31_80F9_821763CBD22F

/**
\file   VlcStatus.hpp
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

#include <QFileInfo>
#include <QMutex>
#include <QNetworkAccessManager>
#include <QObject>
#include <QString>
#include <QUrl>

class QAuthenticator;
class QNetworkReply;

namespace nd {

/** Gets the status of VLC from the status.xml file. */
class VlcStatus : public QObject {
	Q_OBJECT
public:
	VlcStatus(QUrl vlc_address, QString user, QString password);

	void change_details(QUrl vlc_address, QString user, QString password);

	void update();

	QUrl const& address() const;
	QString const& user() const;
	QString const& password() const;

	QString title() const;
	QString artist() const;
	QString album() const;
	QString copyright() const;

	QFileInfo album_art() const;

Q_SIGNALS:
	void updated();

private Q_SLOTS:
	void process_reply(QNetworkReply* reply);
	void authenticate(QNetworkReply* reply, QAuthenticator* authenticator) const;

private:
	QUrl m_url;
	QString m_user, m_password;
	QNetworkAccessManager m_manager;
	QString m_title, m_artist, m_album, m_copyright;
	QFileInfo m_album_art;
	QMutex mutable m_mutex;
};

}

#endif
