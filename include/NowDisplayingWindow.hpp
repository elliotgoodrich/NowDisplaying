#ifndef INCLUDE_GUARD_0919F3B3_2FDE_4623_AED9_AFF2F50E2C30
#define INCLUDE_GUARD_0919F3B3_2FDE_4623_AED9_AFF2F50E2C30

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

#include "Settings.hpp"
#include "QtPtr.hpp"
#include "Themes.hpp"
#include "VlcStatus.hpp"

#include <QLabel>
#include <QMainWindow>
#include <QPoint>
#include <QSize>
#include <QTimer>

class QGridLayout;
class QPoint;

namespace nd {

class NowDisplayingWindow : public QMainWindow {
public:
	explicit NowDisplayingWindow(QWidget* parent);
	~NowDisplayingWindow() override;

Q_SIGNALS:
	void change_theme(QString const& theme);

protected:
	void keyPressEvent(QKeyEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

private Q_SLOTS:
	void update();
	void show_context_menu(const QPoint& pos);
	void show_settings();
	void set_locked(bool locked);
	void set_on_top(bool on_top);
	void set_theme(QString const& theme);

private:
	Settings m_settings;
	VlcStatus m_vlc;
	QGridLayout* m_detail_layout;
	QtPtr<QLabel> m_title, m_artist, m_album, m_copyright, m_album_art;
	QTimer m_timer;
	QSize m_image_size;
	QPoint m_start_drag;
	bool m_locked;
	bool m_on_top;
	Themes m_theme;
	QString m_current_theme;
	QString m_current_app;
};

}

#endif
