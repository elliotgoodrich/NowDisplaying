#ifndef INCLUDE_GUARD_6FCC2718_C379_43D0_BDAD_3842C1D5966C
#define INCLUDE_GUARD_6FCC2718_C379_43D0_BDAD_3842C1D5966C

/**
\file   Settings.hpp
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

#include <QSettings>

class QFileInfo;
class QString;
class QUrl;

namespace nd {

class Settings {
public:
	Settings(QFileInfo ini_file);

	bool locked() const;
	void set_locked(bool locked);

	bool on_top() const;
	void set_on_top(bool on_top);

	QPoint position() const;
	void set_position(QPoint const& position);

	QString theme() const;
	void set_theme(QString const& theme);

	QString application() const;
	void set_application(QString const& application);

	QString vlc_user() const;
	void set_vlc_user(QString const& user);

	QString vlc_password() const;
	void set_vlc_password(QString const& password);

	QUrl vlc_address() const;
	void set_vlc_address(QUrl const& address);

private:
	QSettings m_settings;
};

}

#endif
