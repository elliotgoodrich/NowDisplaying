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
#include <QUrl>

namespace nd {

NowDisplayingWindow::NowDisplayingWindow(QWidget* parent)
: QMainWindow{parent}
, m_vlc{QUrl{"http://localhost:8080/requests/status.xml"}, "", "password"}
, m_title{make_qt<QLabel>("")}
, m_artist{make_qt<QLabel>("")}
, m_album{make_qt<QLabel>("")}
, m_description{make_qt<QLabel>("")}
, m_album_art{make_qt<QLabel>("")}
, m_image_size{100, 100} {

	setWindowFlags(Qt::FramelessWindowHint);

	auto stylesheet = QString("QLabel { color: #ffffff }"
	                          "QMainWindow { background-color: #000000 }");
	setStyleSheet(stylesheet);

	connect(&m_vlc, &VlcStatus::updated, this, &NowDisplayingWindow::update);
	connect(&m_timer, &QTimer::timeout, &m_vlc, &VlcStatus::update);

	auto central_widget = make_qt<QWidget>();
	setCentralWidget(central_widget);

	auto hlayout = make_qt<QHBoxLayout>();
	central_widget->setLayout(hlayout);

	auto image = QPixmap{100, 100};
	image.fill(Qt::black);

	m_album_art = make_qt<QLabel>();
	m_album_art->setPixmap(image);

	hlayout->addWidget(m_album_art);

	auto detail_widget = make_qt<QWidget>();
	m_detail_layout = make_qt<QGridLayout>();
	detail_widget->setLayout(m_detail_layout);
	hlayout->addWidget(detail_widget);

	auto title_label  = make_qt<QLabel>("Title: ");
	auto artist_label = make_qt<QLabel>("Artist: ");
	auto album_label  = make_qt<QLabel>("Album: ");
	auto desc_label   = make_qt<QLabel>("Desc: ");

	m_detail_layout->addWidget(title_label, 0, 0);
	m_detail_layout->addWidget(artist_label, 1, 0);
	m_detail_layout->addWidget(album_label, 2, 0);
	m_detail_layout->addWidget(desc_label, 3, 0);

	m_detail_layout->addWidget(m_title, 0, 1);
	m_detail_layout->addWidget(m_artist, 1, 1);
	m_detail_layout->addWidget(m_album, 2, 1);
	m_detail_layout->addWidget(m_description, 3, 1);

	m_vlc.update();

	m_timer.start(100);
}

void NowDisplayingWindow::update() {
	m_title->setText(m_vlc.title());
	m_artist->setText(m_vlc.artist());
	m_album->setText(m_vlc.album());
	m_description->setText(m_vlc.description());

	auto album_art = QPixmap{m_vlc.album_art().absoluteFilePath()};
	if(album_art.isNull()) {
		album_art = QPixmap{m_image_size};
		album_art.fill(Qt::black);
	} else {
		album_art = album_art.scaled(m_image_size);
	}
	m_album_art->setPixmap(album_art);
}

}
