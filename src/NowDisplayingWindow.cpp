/**
\file   NowDisplayingWindow.cpp
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

#include "NowDisplayingWindow.hpp"
#include "QtPtr.hpp"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QWidget>

namespace nd {

NowDisplayingWindow::NowDisplayingWindow(QWidget* parent)
: QMainWindow{parent} {
	setWindowFlags(Qt::FramelessWindowHint);

	auto central_widget = make_qt<QWidget>();
	setCentralWidget(central_widget);

	auto hlayout = make_qt<QHBoxLayout>();
	central_widget->setLayout(hlayout);

	auto image = QPixmap{100, 100};
	image.fill(Qt::red);

	auto image_widget = make_qt<QLabel>();
	image_widget->setPixmap(image);

	hlayout->addWidget(image_widget);

	auto detail_widget = make_qt<QWidget>();
	auto detail_layout = make_qt<QGridLayout>();
	detail_widget->setLayout(detail_layout);
	hlayout->addWidget(detail_widget);

	auto track_label   = make_qt<QLabel>("Track: ");
	auto track_details = make_qt<QLabel>("Track Name");

	auto artist_label   = make_qt<QLabel>("Artist: ");
	auto artist_details = make_qt<QLabel>("Artist Name");

	auto album_label   = make_qt<QLabel>("Album: ");
	auto album_details = make_qt<QLabel>("Album Name");

	auto license_label   = make_qt<QLabel>("License: ");
	auto license_details = make_qt<QLabel>("License Name");

	detail_layout->addWidget(track_label,   0, 0);
	detail_layout->addWidget(artist_label,  1, 0);
	detail_layout->addWidget(album_label,   2, 0);
	detail_layout->addWidget(license_label, 3, 0);

	detail_layout->addWidget(track_details,   0, 1);
	detail_layout->addWidget(artist_details,  1, 1);
	detail_layout->addWidget(album_details,   2, 1);
	detail_layout->addWidget(license_details, 3, 1);
}

}
