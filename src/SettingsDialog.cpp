/**
\file   SettingsDialog.cpp
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

#include "SettingsDialog.hpp"
#include "QtPtr.hpp"

#include <QDialogButtonBox>
#include <QLabel>
#include <QString>
#include <QUrl>

namespace nd {

SettingsDialog::SettingsDialog(QUrl const& url, QString const& user, QString const& password)
: m_vlc_box{"VLC Settings"}
, m_vlc_user{user}
, m_vlc_password{password}
, m_vlc_url{url.toString(QUrl::None)} {

	m_vlc_user.setFixedWidth(200);
	m_vlc_password.setFixedWidth(200);
	m_vlc_url.setFixedWidth(200);

	setLayout(&m_top_layout);
	m_top_layout.addWidget(&m_vlc_box);

	m_vlc_box.setLayout(&m_vlc_layout);
	m_vlc_layout.addWidget(make_qt<QLabel>("Url:"), 0, 0);
	m_vlc_layout.addWidget(&m_vlc_url, 0, 1);

	m_vlc_layout.addWidget(make_qt<QLabel>("User:"), 1, 0);
	m_vlc_layout.addWidget(&m_vlc_user, 1, 1);

	m_vlc_layout.addWidget(make_qt<QLabel>("Password:"), 2, 0);
	m_vlc_layout.addWidget(&m_vlc_password, 2, 1);

	auto buttons = make_qt<QDialogButtonBox>(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	m_top_layout.addWidget(buttons);
	connect(&*buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(&*buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

QString SettingsDialog::vlc_user() const {
	return m_vlc_user.text();
}

QString SettingsDialog::vlc_password() const {
	return m_vlc_password.text();
}

QUrl SettingsDialog::vlc_address() const {
	return m_vlc_url.text();
}

}
