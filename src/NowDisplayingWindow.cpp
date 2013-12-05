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
#include "RightClickMenu.hpp"
#include "SettingsDialog.hpp"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QKeySequence>
#include <QLabel>
#include <QMouseEvent>
#include <QPixmap>
#include <QString>
#include <QWidget>
#include <QUrl>

#include <utility>
#include <vector>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

namespace nd {

NowDisplayingWindow::NowDisplayingWindow(QWidget* parent)
: QMainWindow{parent}
, m_settings{QDir::currentPath() + "settings.ini"}
, m_vlc{m_settings.vlc_address(), m_settings.vlc_user(), m_settings.vlc_password()}
, m_title{make_qt<QLabel>("")}
, m_artist{make_qt<QLabel>("")}
, m_album{make_qt<QLabel>("")}
, m_copyright{make_qt<QLabel>("")}
, m_album_art{make_qt<QLabel>("")}
, m_image_size{100, 100}
, m_locked{m_settings.locked()}
, m_on_top{m_settings.on_top()}
, m_current_theme{m_settings.theme()}
, m_current_app{m_settings.application()} {

	setWindowFlags(Qt::FramelessWindowHint);
	set_theme(m_settings.theme());
	set_on_top(m_settings.on_top());
	set_locked(m_settings.locked());
	move(m_settings.position());

	m_vlc.update();

	setFixedSize(400, 120);

	setContextMenuPolicy(Qt::CustomContextMenu);

	connect(&m_vlc, &VlcStatus::updated, this, &NowDisplayingWindow::update);
	connect(&m_timer, &QTimer::timeout, &m_vlc, &VlcStatus::update);
	connect(this, &NowDisplayingWindow::customContextMenuRequested,
	        this, &NowDisplayingWindow::show_context_menu);

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

	m_detail_layout->setColumnStretch(0, 0);
	m_detail_layout->setColumnStretch(1, 0);
	m_detail_layout->setColumnStretch(2, 1);

	auto title_label     = make_qt<QLabel>("Title: ");
	auto artist_label    = make_qt<QLabel>("Artist: ");
	auto album_label     = make_qt<QLabel>("Album: ");
	auto copyright_label = make_qt<QLabel>("Copyright: ");

	auto const alignment = Qt::AlignLeft | Qt::AlignVCenter;
	m_detail_layout->addWidget(title_label, 0, 0, alignment);
	m_detail_layout->addWidget(artist_label, 1, 0);
	m_detail_layout->addWidget(album_label, 2, 0);
	m_detail_layout->addWidget(copyright_label, 3, 0);

	m_detail_layout->addWidget(m_title, 0, 1, alignment);
	m_detail_layout->addWidget(m_artist, 1, 1);
	m_detail_layout->addWidget(m_album, 2, 1);
	m_detail_layout->addWidget(m_copyright, 3, 1);

	m_timer.start(100);
}

NowDisplayingWindow::~NowDisplayingWindow() {
	m_settings.set_locked(m_locked);
	m_settings.set_on_top(m_on_top);
	m_settings.set_theme(m_current_theme);
	m_settings.set_application(m_current_app);
	m_settings.set_position(pos());

	// Set VLC stuff
	m_settings.set_vlc_user(m_vlc.user());
	m_settings.set_vlc_password(m_vlc.password());
	m_settings.set_vlc_address(m_vlc.address());
}

void NowDisplayingWindow::keyPressEvent(QKeyEvent* event) {
	if(event->matches(QKeySequence::Quit) || event->key() == Qt::Key_Escape) {
		close();
	}

	if(m_locked) {
		return;
	}

	/// \todo, check that we don't make the window too small or move it off the screen
	if(event->modifiers() & Qt::ControlModifier) {
		auto const height = size().height();
		auto const width = size().width();
		switch(event->key()) {
			case Qt::Key_Up:
				setFixedSize(width, height - 1);
			break;

			case Qt::Key_Right:
				setFixedSize(width + 1, height);
			break;

			case Qt::Key_Down:
				setFixedSize(width, height + 1);
			break;

			case Qt::Key_Left:
				setFixedSize(width - 1, height);
			break;

			default:
			break;
		}
	} else {
		switch(event->key()) {
			case Qt::Key_Up:
				move(pos() - QPoint{0, 1});
			break;

			case Qt::Key_Right:
				move(pos() + QPoint{1, 0});
			break;

			case Qt::Key_Down:
				move(pos() + QPoint{0, 1});
			break;

			case Qt::Key_Left:
				move(pos() - QPoint{1, 0});
			break;

			default:
			break;
		}
	}
}

void NowDisplayingWindow::mousePressEvent(QMouseEvent* event) {
	if(!m_locked && event->button() == Qt::LeftButton) {
		m_start_drag = event->globalPos() - frameGeometry().topLeft();
		event->accept();
	}
}

void NowDisplayingWindow::mouseMoveEvent(QMouseEvent* event) {
	if(!m_locked && event->buttons() & Qt::LeftButton) {
		move(event->globalPos() - m_start_drag);
		event->accept();
	}
}

void NowDisplayingWindow::update() {
	m_title->setText(m_vlc.title());
	m_artist->setText(m_vlc.artist());
	m_album->setText(m_vlc.album());
	m_copyright->setText(m_vlc.copyright());

	auto album_art = QPixmap{m_vlc.album_art().absoluteFilePath()};
	if(album_art.isNull()) {
		album_art = QPixmap{m_image_size};
		album_art.fill(Qt::black);
	} else {
		album_art = album_art.scaled(m_image_size);
	}
	m_album_art->setPixmap(album_art);
}

void NowDisplayingWindow::show_context_menu(const QPoint& pos) {
	auto point = mapToGlobal(pos);
	RightClickMenu menu(std::move(point), m_locked, m_on_top);
	connect(&menu, &RightClickMenu::open_settings, this, &NowDisplayingWindow::show_settings);
	connect(&menu, &RightClickMenu::quit, this, &QMainWindow::close);
	connect(&menu, &RightClickMenu::set_locked, this, &NowDisplayingWindow::set_locked);
	connect(&menu, &RightClickMenu::set_on_top, this, &NowDisplayingWindow::set_on_top);
	connect(&menu, &RightClickMenu::change_theme, this, &NowDisplayingWindow::set_theme);

	QStringList applications{"VLC"};
	auto themes = m_theme.themes();
	menu.exec(applications, m_current_app, themes, m_current_theme);
	/*if(auto selection = meny.exec(point)) {
		qDebug() << "Yes";
	}*/
}

void NowDisplayingWindow::show_settings() {
	SettingsDialog dialog{m_vlc.address(), m_vlc.user(), m_vlc.password(), this};
	if(dialog.exec() == QDialog::Accepted) {
		m_vlc.change_details(dialog.vlc_address(), dialog.vlc_user(), dialog.vlc_password());
	}
}

void NowDisplayingWindow::set_locked(bool locked) {
	m_locked = locked;
}

void NowDisplayingWindow::set_on_top(bool on_top) {
	m_on_top = on_top;
	// Qt doesn't remove the always on top flag
	// (https://bugreports.qt-project.org/browse/QTBUG-30359)
	// Solution provided by Jake Petroules via StackOverflow (http://stackoverflow.com/a/2860768)
#ifdef Q_OS_WIN
	if(m_on_top) {
		SetWindowPos(reinterpret_cast<HWND>(winId()), HWND_TOPMOST, 0, 0, 0, 0,
		             SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	} else {
		SetWindowPos(reinterpret_cast<HWND>(winId()), HWND_NOTOPMOST, 0, 0, 0, 0,
		             SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	}
#else
	auto const flags = m_on_top ? windowFlags() | Qt::WindowStaysOnTopHint
	                            : windowFlags() & ~Qt::WindowStaysOnTopHint;
	setWindowFlags(flags);
#endif
	show();
}

void NowDisplayingWindow::set_theme(QString const& theme) {
	auto const stylesheet = m_theme.stylesheet(theme);
	if(!stylesheet.isEmpty()) {
		m_current_theme = theme;
		setStyleSheet(stylesheet);
	}
}

}
