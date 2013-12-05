#ifndef INCLUDE_GUARD_17379EA8_845A_4776_831F_87D4EB0E81BF
#define INCLUDE_GUARD_17379EA8_845A_4776_831F_87D4EB0E81BF

/**
\file   Themes.hpp
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

#include <QDir>
#include <QStringList>

class QString;

namespace nd {

class Themes {
public:
	Themes();

	QStringList themes() const;

	QString stylesheet(QString const& theme) const;

private:
	QDir m_theme_dir;
	QStringList m_filters;
};

}

#endif
