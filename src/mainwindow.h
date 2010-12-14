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
#include <QTime>

#include <KDE/KAction>
#include <KDE/KConfigDialog>
#include <KDE/KXmlGuiWindow>

#include <MediaInfoInteractivePage.h>
#include <MediaInfoPage.h>
#include <MediaPlaylist.h>
#include <PlaybaKAnimatedSliderWidget.h>
#include <PlaylistWidget.h>

#include <ui_prefs_base.h>

class KStatusNotifierItem;
class KSystemTrayIcon;

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
        Ui::prefs_base ui_prefs_base;
        Ui::MainWindow *ui;
        MediaInfoPage *mip1;
        MediaInfoInteractivePage *mip2;
        QWidget *playlistDockTitleBar;
        QWidget *controlsDockTitleBar;
        QWidget *nullPlaylistDockTitleBar;
        QWidget *nullControlsDockTitleBar;
        KConfigDialog *dialog;
        KAction *mPlayPause;
        KAction *mNext;
        KAction *mPrev;
        KAction *mLoadPlaylist;

        PlaylistWidget *mPlaylistWidget;
        KStatusNotifierItem *mStatusNotifierItem;
//         QAction* addFilesAction;

        MediaPlaylist mMediaPlaylist;
        void setupActions();
protected:
  virtual void saveProperties( KConfigGroup &config);
  virtual void readProperties(const KConfigGroup &config);
public slots:
        void addFiles();
        void setProgressBarValue(qint64);
        void setProgressBarMaximum(int);
        void playPause();
        void progressBarValueChanged(qint64);
        void trackChanged();
        void setVolume(int);
        void toggleMute();
        void togglePlaylistMode();
//         void openMedia();
        void loadPlaylist();
        void savePlaylist();
private slots:
        void showMediaInfoPage2();
        void showMediaInfoPage1();
        void showShortcutsSettingsDialog();
        void optionsPreferences();
};

#endif // MAINWINDOW_H
