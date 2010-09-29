/*
 * PlaybaK - A KDE Multimedia Player.
 * Copyright (C) 2010 PlaybaK Development Team (see AUTHORS file)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see http://www.gnu.org/licenses
 * or write to the Free Software Foundation,Inc., 51 Franklin Street,
 * Fifth Floor, Boston, MA 02110-1301  USA
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PlaybaKAnimatedSliderWidget.h"
#include <kxmlguiwindow.h>
#include "MediaInfoPage.h"
#include "MediaInfoInteractivePage.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public KXmlGuiWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
	PlaybaKAnimatedSliderWidget *test;
	PlaybaKAnimatedSliderWidget *test2;
	PlaybaKAnimatedSliderWidget *test3;
	PlaybaKAnimatedSliderWidget *test4;
	PlaybaKAnimatedSliderWidget *test5;
	PlaybaKAnimatedSliderWidget *test6;
	PlaybaKAnimatedSliderWidget *test7;
	Ui::MainWindow *ui;
	MediaInfoPage* mip1;
	MediaInfoInteractivePage* mip2;
    QWidget *playlistDockTitleBar;
    QWidget *controlsDockTitleBar;
    QWidget *nullPlaylistDockTitleBar;
    QWidget *nullControlsDockTitleBar;
		
private slots:
	void testclick();
	void showMediaInfoPage2();
	void showMediaInfoPage1();
};

#endif // MAINWINDOW_H
