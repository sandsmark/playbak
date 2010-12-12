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

#include <QPushButton>
#include <QTime>

#include <Nepomuk/ResourceManager>

#include <KDE/KIcon>
#include <KDE/KAction>
#include <KDE/KActionCollection>
#include <KDE/KFileDialog>
#include <KDE/KGlobalSettings>
#include <KDE/KMenu>
#include <KDE/KMenuBar>
#include <KDE/KStandardAction>
#include <KDE/KStatusNotifierItem>

#include <PlaybaKFadingButton.h>

#include <mainwindow.h>
#include <settings.h>
#include <ui_mainwindow.h>

MainWindow::MainWindow(QWidget *parent) :
KXmlGuiWindow(parent),
ui(new Ui::MainWindow)
{
        qDebug("setupUI");
        ui->setupUi(this);
        qDebug("Constructor general");
        ui->prevMedia->setIcon(KIcon("media-skip-backward"));
        ui->playMedia->setIcon(KIcon("media-playback-start"));
        ui->nextMedia->setIcon(KIcon("media-skip-forward"));
        ui->muteSwitch->setIcon(KIcon("player-volume"));
        ui->playlistFilterConfigButton->setIcon(KIcon("preferences-other"));
        ui->playMedia->setOverIcon("playglow.png");

        // Playlist's' Buttons
        ui->addMediaItem->setIcon(KIcon("list-add"));
        ui->removeMediaItem->setIcon(KIcon("list-remove"));
        ui->clearPlaylist->setIcon(KIcon("edit-clear-list"));
        ui->undoPlaylistAction->setIcon(KIcon("edit-undo"));
        ui->redoPlaylistAction->setIcon(KIcon("edit-redo"));
        ui->savePlaylist->setIcon(KIcon("document-save"));
        ui->playMode->setIcon(KIcon("media-playlist-repeat"));
        
        mPlayPause = new KAction(KIcon("media-playback-start"),tr("Play media"),this);
        mPlayPause->setText(tr("Play media"));
        mPlayPause->setIcon(KIcon("media-playback-start"));
        connect(mPlayPause,SIGNAL(triggered()),ui->playMedia,SLOT(click()));
        mNext = new KAction(KIcon("media-skip-forward"),tr("Next media"),this);
        mNext->setText(tr("Next media"));
        mNext->setIcon(KIcon("media-skip-forward"));
        connect(mNext,SIGNAL(triggered()),ui->nextMedia,SLOT(click()));
        mPrev = new KAction(KIcon("edia-skip-backward"),tr("Previous media"),this);
        mPrev->setText(tr("Previous media"));
        mPrev->setIcon(KIcon("edia-skip-backward"));
        
        mStatusNotifierItem = new KStatusNotifierItem(this);
        mStatusNotifierItem->setCategory(KStatusNotifierItem::ApplicationStatus);
        mStatusNotifierItem->setToolTipTitle("PlaybaK");
        mStatusNotifierItem->setTitle("PlaybaK");
        mStatusNotifierItem->setIconByName("media-playback-start");
        mStatusNotifierItem->contextMenu()->addAction(mPlayPause);
        mStatusNotifierItem->contextMenu()->addAction(mNext);
        mStatusNotifierItem->contextMenu()->addAction(mPrev);
//         mStatusNotifierItem->setContextMenu(contextMenu);
        
        setAcceptDrops(true);
        qDebug("Vamos a setupActions");
        setupActions();
        qDebug("Luego del seetupActions");
        mip1 = new MediaInfoPage(ui->mediaInfo);
        mip2 = new MediaInfoInteractivePage(ui->mediaInfo);
        ui->mediaInfo->insertWidget(0, mip1);
        ui->mediaInfo->insertWidget(1, mip2);
        ui->mediaInfo->setCurrentIndex(0);
//         mip1->setStyleSheet(QString::fromUtf8("#page {\n"
//                                                       "background-color:\n"
//                                                       "qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ccc, stop: 1.0 #c2c2c2);\n"
//                                                       "border: 1px solid rgb(150, 150, 150);\n"
//                                                       "border-radius: 5px;\n"
//                                                       "}"));
        connect(mip1, SIGNAL(mouseOver()), SLOT(showMediaInfoPage2()));
        connect(mip1, SIGNAL(mouseLeave()), SLOT(showMediaInfoPage1()));
        connect(mip2, SIGNAL(mouseLeave()), SLOT(showMediaInfoPage1()));
        connect(mip2, SIGNAL(ratingChanged(int)), mip1, SLOT(setRating(int)));
        
        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());
        // Create and add the PlaylistWidget to the gui
        QHBoxLayout *playListLayout;
        playListLayout = new QHBoxLayout();
        ui->playlistList->setLayout(playListLayout);
        
        mPlaylistWidget = new PlaylistWidget();
        playListLayout->addWidget(mPlaylistWidget);

//         mMediaPlaylist.setOutputWidget(ui->nowPlayingPage);
        //TODO Cunado se reproduzca un video, establecer mMediaPlaylist.setOutputWidget(ui->nowPlayingPage);
        mMediaPlaylist.setOutputWidget(0x0L);
        mMediaPlaylist.setMode(MediaPlaylist::Mode::LOOP_PLAYLIST);
        connect(ui->volumeBar,SIGNAL(valueChanged(int)),this,SLOT(setVolume(int)));
        connect(mPlaylistWidget,SIGNAL(play(int)),&mMediaPlaylist, SLOT(play(int)));
        connect(mPlaylistWidget,SIGNAL(itemAdded(MediaItem*)),&mMediaPlaylist, SLOT(addMediaItem(MediaItem*)));
        connect(&mMediaPlaylist,SIGNAL(tick(qint64)),this,SLOT(setProgressBarValue(qint64)));
        connect(&mMediaPlaylist,SIGNAL(tick(qint64)),this,SLOT(progressBarValueChanged(qint64)));
        connect(&mMediaPlaylist,SIGNAL(totalTime(int)),this,SLOT(setProgressBarMaximum(int)));
        connect(&mMediaPlaylist,SIGNAL(trackChanged()),this,SLOT(trackChanged()));
        connect(ui->muteSwitch, SIGNAL(clicked()),this, SLOT(toggleMute()));
        connect(ui->playMedia, SIGNAL(clicked()),this, SLOT(playPause()));
        connect(ui->nextMedia, SIGNAL(clicked()),&mMediaPlaylist, SLOT(playNext()));
        connect(ui->prevMedia, SIGNAL(clicked()),&mMediaPlaylist, SLOT(playPrevious()));
        connect(ui->addMediaItem,SIGNAL(clicked()),this,SLOT(addFiles()));
        connect(ui->trackProgressBar,SIGNAL(valueChanged(int)),&mMediaPlaylist,SLOT(setTick(int)));
        connect(ui->removeMediaItem,SIGNAL(clicked()),mPlaylistWidget,SLOT(removeSelecteds()));
        connect(mPlaylistWidget,SIGNAL(removedItem(int)),&mMediaPlaylist,SLOT(remove(int)));
        connect(ui->clearPlaylist,SIGNAL(clicked()),mPlaylistWidget,SLOT(clearPlaylist()));
        connect(ui->savePlaylist,SIGNAL(clicked()),this,SLOT(savePlaylist()));
        connect(ui->playMode,SIGNAL(clicked()),this,SLOT(togglePlaylistMode()));
        ui->volumeBar->setMinimum(0);
        ui->volumeBar->setMaximum(100);
        ui->volumeBar->setValue(100);
        setVolume(ui->volumeBar->value());

        
        if (Nepomuk::ResourceManager::instance()->init())
          qDebug("Nepomuk problem: Can't init.");
        
}

#include <QTimer>

void MainWindow::playPause(){
  qDebug("PlayPause");
  if (mMediaPlaylist.state() == Phonon::PlayingState){
    ui->playMedia->setIcon(KIcon("media-playback-pause"));
  }
  else{
    ui->playMedia->setIcon(KIcon("media-playback-start"));
  }
  mMediaPlaylist.playPause();
}

void MainWindow::toggleMute(){
  if (mMediaPlaylist.isMute()){
    ui->muteSwitch->setIcon(KIcon("player-volume"));
    mMediaPlaylist.setMute(false);
  } else {
    ui->muteSwitch->setIcon(KIcon("player-volume-muted"));
    mMediaPlaylist.setMute();
  }

}

void MainWindow::togglePlaylistMode(){
  switch(mMediaPlaylist.mode())
  {
    case MediaPlaylist::Mode::NORMAL:
      ui->playMode->setIcon(KIcon("media-playlist-repeat"));
      ui->playMode->setToolTip(tr("Repeat media"));
      mMediaPlaylist.setMode(MediaPlaylist::Mode::LOOP_MEDIA);
      break;
    case MediaPlaylist::Mode::LOOP_MEDIA:
      ui->playMode->setIcon(KIcon("media-playlist-repeat"));
      ui->playMode->setToolTip(tr("Repeat playlist"));
      mMediaPlaylist.setMode(MediaPlaylist::Mode::LOOP_PLAYLIST);
      break;
    case MediaPlaylist::Mode::LOOP_PLAYLIST:
      ui->playMode->setIcon(KIcon("media-playlist-shuffle"));
      ui->playMode->setToolTip(tr("Random media"));
      mMediaPlaylist.setMode(MediaPlaylist::Mode::SHUFFLE_ALL);
      break;
    case MediaPlaylist::Mode::SHUFFLE_ALL:
      ui->playMode->setIcon(KIcon("view-media-playlist"));
      ui->playMode->setToolTip(tr("Normal mode"));
      mMediaPlaylist.setMode(MediaPlaylist::Mode::NORMAL);
      break;
  }
}

void MainWindow::setVolume(int value){
  qreal volume = (qreal)(value) / 100.0;
  mMediaPlaylist.setVolume(volume);
}

void MainWindow::trackChanged(){
  if(!mMediaPlaylist.mediaItem()){
    ui->trackLenght->setText("00:00");
    return;
  }
  
  int value = mMediaPlaylist.totalTime() / 1000;
  
  int min = value / 60;
  int sec = value % 60;
  QString minString;
  QString secString;
  
  if(min < 10)
    minString = QString('0') + QString::number(min);
  else
    minString = QString::number(min);
  
  if(sec < 10)
    secString = QString('0') + QString::number(sec);
  else
    secString = QString::number(sec);
  
  ui->trackLenght->setText( minString + QString(':') + secString);
  
  if ( MediaInfoPage *w = qobject_cast< MediaInfoPage* >(ui->mediaInfo->widget(0)))
    w->setMediaItem(mMediaPlaylist.mediaItem());
  if (MediaInfoInteractivePage *w = qobject_cast< MediaInfoInteractivePage* >(ui->mediaInfo->widget(1)))
    w->setMediaItem(mMediaPlaylist.mediaItem());
}

//TODO Que admita horas.
void MainWindow::progressBarValueChanged(qint64 value){
//   if(!mMediaPlaylist.mediaItem())
//   {
//     ui->trackActualTime->setText("00:00");
//     return;
//   }
  value = value / 1000;
  
  int min = value / 60;
  int sec = value % 60;
  QString minString;
  QString secString;
  
  if(min < 10)
    minString = QString('0') + QString::number(min);
  else
    minString = QString::number(min);

  if(sec < 10)
    secString = QString('0') + QString::number(sec);
  else
    secString = QString::number(sec);
  
  ui->trackActualTime->setText( minString + QString(':') + secString);
}

void MainWindow::setProgressBarValue(qint64 value){
  ui->trackProgressBar->setValue(value);
}

void MainWindow::setProgressBarMaximum(int value){
  ui->trackProgressBar->setMaximum(value);
}

void MainWindow::showMediaInfoPage2()
{
  if(ui->mediaInfo->currentIndex() != 1)
          ui->mediaInfo->setCurrentIndex(1);
}

void MainWindow::loadPlaylist(){
  QString fileName = KFileDialog::getOpenFileName(KGlobalSettings::desktopPath(),"*.m3u");
  if ( !fileName.isEmpty() )
  {
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QStringList playlist;
    while (!file.atEnd()) {
      QByteArray line = file.readLine();
      line.remove(line.size() - 1,1); // Remove the character '\n'
      QString mediaName(line);
      playlist << mediaName;
    }
    file.close();
    mPlaylistWidget->addItem(playlist);
  }
}

void MainWindow::savePlaylist(){
  
  QString fileName = KFileDialog::getSaveFileName(KUrl(KGlobalSettings::desktopPath()),"*.m3u");
  if ( !fileName.isEmpty() )
  {
    QFile file(fileName);
    file.open(QIODevice::Truncate | QIODevice::WriteOnly);
    for(int i = 0; i < mMediaPlaylist.count(); ++i)
    {
      QByteArray row(mMediaPlaylist.mediaItem(i)->url().toEncoded());
      row.append("\n");
      file.write(row);
    }
    file.close();
  }
}

void MainWindow::showMediaInfoPage1()
{
  if(ui->mediaInfo->currentIndex() != 0)
          ui->mediaInfo->setCurrentIndex(0);
}

void MainWindow::optionsPreferences()
{
    // this show the configuration dialog

    //avoid to have 2 dialogs shown
    if ( KConfigDialog::showDialog ( "settings" ) )
    {
        return;
    }

    dialog = new KConfigDialog ( this, "settings", Settings::self() );
    dialog->setFaceType ( KPageDialog::List );
    QWidget *baseSettingsDlg = new QWidget;
    ui_prefs_base.setupUi ( baseSettingsDlg );
    dialog->addPage ( baseSettingsDlg, i18n ( "General" ), "preferences-other" );
    dialog->setAttribute ( Qt::WA_DeleteOnClose );
    dialog->show();
}

void MainWindow::setupActions()
{
    mLoadPlaylist = new KAction(tr("Load Playlist"), this);
    mLoadPlaylist->setText(tr("Load Playlist"));
    connect(mLoadPlaylist,SIGNAL(triggered()),this,SLOT(loadPlaylist()));
    actionCollection()->addAction("lpl",mLoadPlaylist);

    // It adds the action in the menu bar, created on playbakui.rc model.
    KStandardAction::quit ( qApp, SLOT ( closeAllWindows() ), actionCollection() );
    KStandardAction::preferences ( this, SLOT ( optionsPreferences() ), actionCollection() ); 

    // FIXME: write the correct dir
    createGUI("playbakui.rc");
//     setupGUI(Create | Keys);

}

void MainWindow::addFiles(){
//   KFileDialog *mFileDialog = new KFileDialog(KUrl("/home"),"",this);
//   QStringList mimes;
//   mimes << "audio/*";
//   mFileDialog->setMimeFilter(mimes);

//   files = KFileDialog::getOpenFileNames(KUrl("/home/"), tr("*.*"), this);
mPlaylistWidget->addItem( KFileDialog::getOpenFileNames(KGlobalSettings::desktopPath(), "udio/aac audio/ac3 audio/midi audio/mp3 audio/ogg audio/wav", this) );

//   ((PlaylistWidget*)(ui->playlistList->childAt(0,0)))->addItem(mFileDialog->getOpenFileNames());
//   delete mFileDialog;
}


MainWindow::~MainWindow()
{
  delete ui;
}
#include <mainwindow.moc>