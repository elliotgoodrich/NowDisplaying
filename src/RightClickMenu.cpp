/**
\file   RightClickMenu.cpp
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

#include "RightClickMenu.hpp"

#include <QAction>
#include <QActionGroup>
#include <QMenu>
#include <QPoint>
#include <QString>
#include <QStringList>

#include <utility>

namespace nd {

RightClickMenu::RightClickMenu(QPoint position, bool locked, bool on_top)
: m_position{std::move(position)}
, m_locked{locked}
, m_on_top{on_top} {
}

void RightClickMenu::exec(QStringList const& applications, QString const& app_selected,
                          QStringList const& themes, QString const& theme_selected) const {
	QMenu main_menu;
	auto settings_action = main_menu.addAction("Settings...");
	connect(settings_action, &QAction::triggered, this, &RightClickMenu::open_settings);

	QMenu app_menu{"Applications"};
	QActionGroup app_group{&app_menu};
	connect(&app_group, &QActionGroup::triggered, this, &RightClickMenu::application_triggered);
	main_menu.addMenu(&app_menu);

	for(auto const& application : applications) {
		auto app_action = app_menu.addAction(application);
		app_action->setCheckable(true);
		app_action->setActionGroup(&app_group);
		if(application == app_selected) {
			app_action->setChecked(true);
		}
	}

	QMenu theme_menu{"Theme"};
	QActionGroup theme_group{&theme_menu};
	connect(&theme_group, &QActionGroup::triggered, this, &RightClickMenu::theme_triggered);
	main_menu.addMenu(&theme_menu);

	for(auto const& theme : themes) {
		auto theme_action = theme_menu.addAction(theme);
		theme_action->setCheckable(true);
		theme_action->setActionGroup(&theme_group);
		if(theme == theme_selected) {
			theme_action->setChecked(true);
		}
	}

	main_menu.addSeparator();
	auto lock_action = main_menu.addAction("Lock");
	connect(lock_action, &QAction::triggered, this, &RightClickMenu::toggle_lock);
	lock_action->setCheckable(true);
	lock_action->setChecked(m_locked);

	auto on_top_action = main_menu.addAction("Always on top");
	connect(on_top_action, &QAction::triggered, this, &RightClickMenu::toggle_on_top);
	on_top_action->setCheckable(true);
	on_top_action->setChecked(m_on_top);

	main_menu.addSeparator();
	auto about_action = main_menu.addAction("About");
	connect(about_action, &QAction::triggered, this, &RightClickMenu::about);

	auto quit_action = main_menu.addAction("Quit");
	connect(quit_action, &QAction::triggered, this, &RightClickMenu::quit);
	main_menu.exec(m_position);
}

void RightClickMenu::application_triggered(QAction* action) {
	emit change_application(action->text());
}

void RightClickMenu::theme_triggered(QAction* action) {
	emit change_theme(action->text());
}

void RightClickMenu::toggle_lock() {
	emit set_locked(!m_locked);
}

void RightClickMenu::toggle_on_top() {
	emit set_on_top(!m_on_top);
}

}
