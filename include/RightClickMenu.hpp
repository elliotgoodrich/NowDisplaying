#ifndef INCLUDE_GUARD_D5B392AB_4E52_431C_972D_095C1EBD11CD
#define INCLUDE_GUARD_D5B392AB_4E52_431C_972D_095C1EBD11CD

/**
\file   RightClickMenu.hpp
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

#include <QObject>
#include <QPoint>

class QAction;
class QString;
class QStringList;

namespace nd {

class RightClickMenu : public QObject {
	Q_OBJECT
public:
	RightClickMenu(QPoint position, bool locked, bool on_top);

	void exec(QStringList const& applications, QString const& app_selected,
	          QStringList const& themes, QString const& theme_selected) const;

Q_SIGNALS:
	void open_settings();
	void set_locked(bool locked);
	void set_on_top(bool on_top);
	void change_application(QString const& app);
	void change_theme(QString const& theme);
	void about();
	void quit();

private Q_SLOTS:
	void application_triggered(QAction* action);
	void theme_triggered(QAction* action);
	void toggle_lock();
	void toggle_on_top();

private:
	QPoint m_position;
	bool m_locked;
	bool m_on_top;
};

}

#endif
