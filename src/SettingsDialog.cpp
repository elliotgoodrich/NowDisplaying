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
#include <QString>
#include <QUrl>

namespace nd {

SettingsDialog::SettingsDialog(QUrl const& url, QString const& user, QString const& password,
                               QWidget* parent)
: QDialog(parent)
, m_setting_box{"Main Settings"}
, m_vlc_box{"VLC Settings"}
, m_vlc_user{user}
, m_vlc_password{password}
, m_vlc_url{url.toString(QUrl::None)} {

	setLayout(&m_top_layout);
	m_top_layout.addWidget(&m_setting_box);
	m_top_layout.addWidget(&m_vlc_box);

	m_setting_box.setLayout(&m_setting_layout);

	m_vlc_box.setLayout(&m_vlc_layout);
	m_vlc_layout.addWidget(&m_vlc_url);
	m_vlc_layout.addWidget(&m_vlc_user);
	m_vlc_layout.addWidget(&m_vlc_password);

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
