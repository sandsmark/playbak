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
#include <MediaPlaylist.h>

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

  //! These 'static' media info widget.
  MediaInfoPage *mip1;

  //! These 'dynamic' media info widget.
  MediaInfoInteractivePage *mip2;
  /**
    * NOTE This is ONLY an idea, but we don't think implement it for a long time.
    */
  //BEGIN
  QWidget *playlistDockTitleBar;
  QWidget *controlsDockTitleBar;
  QWidget *nullPlaylistDockTitleBar;
  QWidget *nullControlsDockTitleBar;
  //END

  //! The config dialog.
  KConfigDialog *dialog;

  //! The Playback's GLOBAL config.
  KConfigGroup *mGlobalConfig;

  //! Play/Pause action.
  KAction *mPlayPause;

  //! Next track action.
  KAction *mNext;

  //! Previous track action.
  KAction *mPrev;

  //! Load playlist action.
  KAction *mLoadPlaylist;

  //! The Playlist widget.
  MediaPlaylist *mPlaylistWidget;

  //! Status notifier.
  KStatusNotifierItem *mStatusNotifierItem;

  //! The media playlist manager. This is the logical manager, no the visual manager.
//   MediaPlaylist *mMediaPlaylist;

  //! Setup all the actions like play media, load playlist, etc
  void setupActions();

  //! The Playback's configuration interface.
  KConfig *mConfig;

  //! The Playback's LOCAL config. This is useful to restore sessions.
  KConfigGroup *mGroup;

  //! The media items.
  QList<MediaItem*> mMediaItems;

protected:

  //! Save the actual state of the application.
  /*!
   * \param config Where you want save it.
   */
  virtual void saveProperties( KConfigGroup *config);

  //! Restore a state of the application.
  /*!
   * \param config Where you want load it.
   */
  virtual void readProperties(const KConfigGroup *config);

protected slots:
  //! Close all application's windows.
  /*!
   * Depdens of configuration.
   * If is specified that may minimize to systray, then do it, else close the application.
   */
  void closeAllWindows();
public slots:
  //! 'Captures' the close action and hide the application in the systray.
  virtual bool queryClose();

  //! 'Captures' the close action, save the actual state of the application and exit.
  virtual bool queryExit();
  
  //! Displays the 'Open Files' dialog.
  void addFiles();
  
  //! Set the progress bar max value.
  /*!
   * \param value The maximum posible progress bar value.
   */
  void setProgressBarMaximum(qint64 value);

  //! Toggle between play and pause states.
  void playPause();

  //! When the progress bar value change, this updates the UI's elements.
  /*!
   * \param value The new progress bar value.
   */
  void progressBarValueChanged(qint64 value);

  //! When the progress bar value change, this updates the UI's elements.
  void trackChanged();

  //! Set the media volume value.
  void setVolume(int);

  //! Toggle mute state.
  void toggleMute();

  //! Toggle the playlist mode. Repeat all, repeat one, random, etc
  void togglePlaylistMode();
//         void openMedia();

  //! Load a playlist.
  void loadPlaylist();

  //! Save a playlist.
  void savePlaylist();
private slots:
  //! Show the second media info widget's page.
  void showMediaInfoPage2();

  //! Show the first media info widget's page.
  void showMediaInfoPage1();

  //! Show the shortcuts settings dialog.
  void showShortcutsSettingsDialog();

  //! Show the settings dialog.
  void showSettingsDialog();
  
private:
  bool eventFilter(QObject *obj, QEvent *ev);
};

#endif // MAINWINDOW_H
