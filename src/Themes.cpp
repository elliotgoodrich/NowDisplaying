/**
\file   Themes.cpp
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

#include "Themes.hpp"

#include <QTextStream>

namespace nd {

Themes::Themes()
: m_theme_dir{QDir::currentPath() + "/themes/"}
, m_filters{"*.theme"} {
}

QStringList Themes::themes() const {
	auto const theme_files = m_theme_dir.entryInfoList(m_filters, QDir::Files);
	QStringList themes;
	themes.reserve(theme_files.size());
	for(auto const& theme_file : theme_files) {
		themes.push_back(theme_file.baseName());
	}
	return themes;
}

QString Themes::stylesheet(QString const& theme) const {
	QFile file{m_theme_dir.filePath(theme + ".theme")};
	if(file.exists()) {
		if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QTextStream in(&file);
			return in.readAll();
		}
	}
	return "";
}


}
