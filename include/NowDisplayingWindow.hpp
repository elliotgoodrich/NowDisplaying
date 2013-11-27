/**
\file   NowDisplayingWindow.hpp
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

#ifndef INCLUDE_GUARD_0919F3B3_2FDE_4623_AED9_AFF2F50E2C30
#define INCLUDE_GUARD_0919F3B3_2FDE_4623_AED9_AFF2F50E2C30

#include <QMainWindow>

namespace nd {

class NowDisplayingWindow : public QMainWindow {
public:
explicit NowDisplayingWindow(QWidget* parent);
};

}

#endif
