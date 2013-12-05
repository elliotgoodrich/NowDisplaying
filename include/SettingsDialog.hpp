#ifndef INCLUDE_GUARD_C0B9937C_3737_44EE_A462_476E533264F6
#define INCLUDE_GUARD_C0B9937C_3737_44EE_A462_476E533264F6

/**
\file   SettingsDialog.hpp
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

#include <QDialog>
#include <QGroupBox>
#include <QLineEdit>
#include <QVBoxLayout>

class QString;
class QUrl;

namespace nd {

class SettingsDialog : public QDialog {
public:
	explicit SettingsDialog(QUrl const& url, QString const& user, QString const& password,
	                        QWidget* parent);

	QString vlc_user() const;
	QString vlc_password() const;
	QUrl vlc_address() const;

private:
	QGroupBox m_setting_box, m_vlc_box;
	QVBoxLayout m_top_layout, m_setting_layout, m_vlc_layout;
	QLineEdit m_vlc_user, m_vlc_password, m_vlc_url;
};


}

#endif
