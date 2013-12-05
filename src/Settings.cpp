/**
\file   Settings.cpp
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

#include "Settings.hpp"

#include <QFileInfo>
#include <QPoint>
#include <QSettings>
#include <QString>
#include <QUrl>
#include <QVariant>

#include <utility>

namespace nd {

Settings::Settings(QFileInfo ini_file)
: m_settings{ini_file.absoluteFilePath(), QSettings::IniFormat} {
}

bool Settings::locked() const {
	return m_settings.value("Locked", false).toBool();
}

void Settings::set_locked(bool locked) {
	m_settings.setValue("Locked", locked);
}

bool Settings::on_top() const {
	return m_settings.value("OnTop", false).toBool();
}

void Settings::set_on_top(bool on_top) {
	m_settings.setValue("OnTop", on_top);
}

QPoint Settings::position() const {
	return m_settings.value("Position", QPoint{0, 0}).toPoint();
}

void Settings::set_position(QPoint const& position) {
	m_settings.setValue("Position", position);
}

QString Settings::theme() const {
	return m_settings.value("Theme", "Default").toString();
}

void Settings::set_theme(QString const& theme) {
	m_settings.setValue("Theme", theme);
}

QString Settings::application() const {
	return m_settings.value("Application", "VLC").toString();
}

void Settings::set_application(QString const& application) {
	m_settings.setValue("Application", application);
}

QString Settings::vlc_user() const {
	return m_settings.value("VlcUser", "").toString();
}

void Settings::set_vlc_user(QString const& user) {
	m_settings.setValue("VlcUser", user);
}

QString Settings::vlc_password() const {
	return m_settings.value("VlcPassword", "").toString();
}

void Settings::set_vlc_password(QString const& password) {
	m_settings.setValue("VlcPassword", password);
}

QUrl Settings::vlc_address() const {
	return m_settings.value("VlcAddress", QUrl{"http://localhost:8080/request/status.xml"}).toUrl();
}

void Settings::set_vlc_address(QUrl const& address) {
	m_settings.setValue("VlcAddress", address);
}


}
