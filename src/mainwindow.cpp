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
#include <Nepomuk/ResourceManager>

#include <KDE/KApplication>
#include <KDE/KIcon>
#include <KDE/KAction>
#include <KDE/KActionCollection>
#include <KDE/KFileDialog>
#include <KDE/KGlobalAccel>
#include <KDE/KGlobalSettings>
#include <KDE/KMenu>
#include <KDE/KMenuBar>
#include <KDE/KShortcutsDialog>
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
        ui->setupUi(this);
	
        //! Set this application's name to PlaybaK
        setObjectName("PlaybaK");

        //! PlaybaK accept droped items.
        setAcceptDrops(true);
        
        //! Define button's icons.
        ui->prevMedia->setIcon(KIcon("media-skip-backward"));
        ui->playMedia->setIcon(KIcon("media-playback-start"));
        ui->nextMedia->setIcon(KIcon("media-skip-forward"));
        ui->muteSwitch->setIcon(KIcon("player-volume"));
        ui->playlistFilterConfigButton->setIcon(KIcon("preferences-other"));
        ui->playMedia->setOverIcon("playglow.png");
        ui->addMediaItem->setIcon(KIcon("list-add"));
        ui->removeMediaItem->setIcon(KIcon("list-remove"));
        ui->clearPlaylist->setIcon(KIcon("edit-clear-list"));
        ui->undoPlaylistAction->setIcon(KIcon("edit-undo"));
        ui->redoPlaylistAction->setIcon(KIcon("edit-redo"));
        ui->savePlaylist->setIcon(KIcon("document-save"));
        ui->playMode->setIcon(KIcon("media-playlist-repeat"));


        //! Create the action collection for shortcuts, ie.
        actionCollection()->setObjectName("PlaybaK Action Collection");
        actionCollection()->setConfigGroup("PlaybaK");
        actionCollection()->setConfigGlobal(true);

        //! The main actions
        setupActions();

        //! The top rating and info pages (stars and info)
        mip1 = new MediaInfoPage(ui->mediaInfo);
        mip2 = new MediaInfoInteractivePage(ui->mediaInfo);
        ui->mediaInfo->insertWidget(0, mip1);
        ui->mediaInfo->insertWidget(1, mip2);
        ui->mediaInfo->setCurrentIndex(0);

        connect(mip1, SIGNAL(mouseOver()), SLOT(showMediaInfoPage2()));
        connect(mip1, SIGNAL(mouseLeave()), SLOT(showMediaInfoPage1()));
        connect(mip2, SIGNAL(mouseLeave()), SLOT(showMediaInfoPage1()));
        connect(mip2, SIGNAL(ratingChanged(int)), mip1, SLOT(setRating(int)));
        
        //! Create and add the PlaylistWidget to the gui
//         QHBoxLayout *playListLayout;
//         playListLayout = new QHBoxLayout;
//         ui->playlist->setLayout(playListLayout);
//         ui->playlist->setLayout(playListLayout);
//         ui->playlist = new MediaPlaylist();
//         ui->playlistList = ui->playlist;
//         playListLayout->addWidget(ui->playlist);

//         TODO Cunado se reproduzca un video, establecer ui->playlist->setOutputWidget(ui->nowPlayingPage);
        ui->playlist->setOutputWidget(ui->nowPlayingPage);
//         ui->playlist->setOutputWidget(0x0L);
        ui->playlist->setMode(MediaPlaylist::Mode::LOOP_PLAYLIST);
        
        connect(ui->volumeBar,        SIGNAL(valueChanged(int)),     this,            SLOT(setVolume(int)));
//         connect(ui->playlist,      SIGNAL(play(int)),             &ui->playlist, SLOT(play(int)));
//         connect(ui->playlist,      SIGNAL(itemAdded(MediaItem*)), &ui->playlist, SLOT(addMediaItem(MediaItem*)));
        connect(ui->playlist,      SIGNAL(tick(qint64)),          this,            SLOT(progressBarValueChanged(qint64)));
        connect(ui->playlist,      SIGNAL(trackChanged()),        this,            SLOT(trackChanged()));
        connect(ui->playlist,      SIGNAL(totalTime(qint64)),     this,            SLOT(setProgressBarMaximum(qint64)));
        connect(ui->muteSwitch,       SIGNAL(clicked()),             this,            SLOT(toggleMute()));
        connect(ui->playMedia,        SIGNAL(clicked()),             this,            SLOT(playPause()));
        connect(ui->nextMedia,        SIGNAL(clicked()),             ui->playlist, SLOT(playNext()));
        connect(ui->prevMedia,        SIGNAL(clicked()),             ui->playlist, SLOT(playPrevious()));
        connect(ui->addMediaItem,     SIGNAL(clicked()),             this,            SLOT(addFiles()));
        connect(ui->trackProgressBar, SIGNAL(valueChanged(int)),     ui->playlist, SLOT(setTick(int)));
        connect(ui->removeMediaItem,  SIGNAL(clicked()),             ui->playlist, SLOT(removeSelecteds()));
//         connect(ui->playlist,      SIGNAL(removedItem(int)),      &ui->playlist, SLOT(remove(int)));
        connect(ui->clearPlaylist,    SIGNAL(clicked()),             ui->playlist, SLOT(clearPlaylist()));
        connect(ui->savePlaylist,     SIGNAL(clicked()),             this,            SLOT(savePlaylist()));
        connect(ui->playMode,         SIGNAL(clicked()),             this,            SLOT(togglePlaylistMode()));
        
//         connect(ui->playlistScrollArea,      SIGNAL(),     ui->playlistScrollArea,            SLOT());
//         connect(ui->playlist,      SIGNAL(sizeChanged(qint64))),     ui->playlistScrollArea,            SLOT());

                
        ui->volumeBar->setMinimum(0);
        ui->volumeBar->setMaximum(100);
        ui->volumeBar->setValue(100);
        setVolume(ui->volumeBar->value());
        
//         ui->playlistScrollArea->setWidget(ui->playlist);

//         readProperties(this->autoSaveConfigGroup())
        
        if (Nepomuk::ResourceManager::instance()->init())
          qDebug("Nepomuk's problem: Can't init.");

//         mConfig = KGlobal::config().data();
        mConfig = kapp->sessionConfig();
        mGroup = new KConfigGroup(mConfig,"PlaybaK Session");
//         mGroup = &mConfig->group("PlaybaK");
        readProperties(mGroup);

        //! Creates global shortcuts configuration.
        mGlobalConfig = new KConfigGroup(KGlobal::config()->group(actionCollection()->configGroup()));

//         readProperties(&kapp->sessionConfig()->group("PlaybaK"));
//           readProperties(&KGlobal::config().operator->()->group("PlaybaK"));
        
}

void MainWindow::playPause(){
  if (ui->playlist->state() == Phonon::PlayingState){
    ui->playMedia->setIcon(KIcon("media-playback-pause"));
  } else {
    ui->playMedia->setIcon(KIcon("media-playback-start"));
  }
  ui->playlist->playPause();
}

void MainWindow::toggleMute(){
  if (ui->playlist->isMute()){
    ui->muteSwitch->setIcon(KIcon("player-volume"));
    ui->playlist->setMute(false);
  } else {
    ui->muteSwitch->setIcon(KIcon("player-volume-muted"));
    ui->playlist->setMute();
  }

}

void MainWindow::togglePlaylistMode(){
  switch(ui->playlist->mode())
  {
    case MediaPlaylist::Mode::NORMAL:
      ui->playMode->setIcon(KIcon("media-playlist-repeat"));
      ui->playMode->setToolTip(tr("Repeat media"));
      ui->playlist->setMode(MediaPlaylist::Mode::LOOP_MEDIA);
      break;
    case MediaPlaylist::Mode::LOOP_MEDIA:
      ui->playMode->setIcon(KIcon("media-playlist-repeat"));
      ui->playMode->setToolTip(tr("Repeat playlist"));
      ui->playlist->setMode(MediaPlaylist::Mode::LOOP_PLAYLIST);
      break;
    case MediaPlaylist::Mode::LOOP_PLAYLIST:
      ui->playMode->setIcon(KIcon("media-playlist-shuffle"));
      ui->playMode->setToolTip(tr("Random media"));
      ui->playlist->setMode(MediaPlaylist::Mode::SHUFFLE_ALL);
      break;
    case MediaPlaylist::Mode::SHUFFLE_ALL:
      ui->playMode->setIcon(KIcon("view-media-playlist"));
      ui->playMode->setToolTip(tr("Normal mode"));
      ui->playlist->setMode(MediaPlaylist::Mode::NORMAL);
      break;
  }
}

void MainWindow::setVolume(int value){
  ui->playlist->setVolume((qreal)(value) / 100.0);
}


void MainWindow::trackChanged(){
  //! This is needed ever, because ever starts at 0.
  ui->trackCurrentTime->setText("00:00");

  //! If there aren't items in the playlist, set a 'null' all the visual values.
  if( mMediaItems.empty() ){
    ui->trackLenght->setText("00:00");
    ui->trackProgressBar->setMaximum(0);
    ui->trackProgressBar->setValue(0);
    ui->trackProgressBar->setMediaObject(0x0L);
    return;
  }

  //! Set the current track lenght time label's value.
  //BEGIN
  qint64 value = ui->playlist->currentTotalTime() / 1000;
  setProgressBarMaximum(ui->playlist->currentTotalTime());
  qint64 min = value / 60;
  qint64 sec = value % 60;
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
  //END

  //! Pass the new current track to the media info widget.
  //BEGIN
  if ( MediaInfoPage *w = qobject_cast< MediaInfoPage* >(ui->mediaInfo->widget(0)))
    w->setMediaItem(ui->playlist->mediaItem());
  if (MediaInfoInteractivePage *w = qobject_cast< MediaInfoInteractivePage* >(ui->mediaInfo->widget(1)))
    w->setMediaItem(ui->playlist->mediaItem());
  //END

  //! Pass the new current track to the track progress bar widget.
  ui->trackProgressBar->setMediaObject(ui->playlist->mediaObject());
}

//TODO Que admita horas.
void MainWindow::progressBarValueChanged(qint64 value){
  //! Updates the current track time label's value.
  /*! TODO Maybe this block can be a 'helper function' ( intToTime() ) */
  //BEGIN

  //! If there aren't items in the playlist, set a 'null' all the visual values.
  if( mMediaItems.empty() )
  {
    ui->trackCurrentTime->setText("00:00");
    return;
  }
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
  
  ui->trackCurrentTime->setText( minString + QString(':') + secString);
  //END
}

void MainWindow::setProgressBarMaximum(qint64 value){
  qint64 l_value = ui->playlist->currentTotalTime() / 1000;
  qint64 min = l_value / 60;
  qint64 sec = l_value % 60;
  QTime total = QTime(0,min,sec);
  ui->trackLenght->setText(total.toString("mm:ss"));
  ui->trackProgressBar->setMaximum(value);
}

void MainWindow::showMediaInfoPage2()
{
  if(ui->mediaInfo->currentIndex() != 1)
    ui->mediaInfo->setCurrentIndex(1);
}

void MainWindow::loadPlaylist(){
  QString fileName = KFileDialog::getOpenFileName(KGlobalSettings::desktopPath(),"*.m3u *.pls");
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

    QList<MediaItem*> partialMediaItemsList;
    int filesQuant = playlist.size();
    for(int i = 0; i < filesQuant; ++i)
      partialMediaItemsList.append(new MediaItem(playlist[i],true));

    mMediaItems.append(partialMediaItemsList);

    ui->playlist->addItems( &partialMediaItemsList );
    ui->playlist->addItems( &partialMediaItemsList );
    
  }
}

void MainWindow::savePlaylist(){
  
  QString fileName = KFileDialog::getSaveFileName(KUrl(KGlobalSettings::desktopPath()),"*.m3u");
  if ( !fileName.isEmpty() )
  {
    QFile file(fileName);
    file.open(QIODevice::Truncate | QIODevice::WriteOnly);
    for(int i = 0; i < ui->playlist->count(); ++i)
    {
      QByteArray row(ui->playlist->mediaItem(i)->url().toEncoded());
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

void MainWindow::showSettingsDialog()
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

bool MainWindow::eventFilter(QObject* obj, QEvent* ev)
{
    return true;
    return QObject::eventFilter(obj, ev);
}


void MainWindow::setupActions()
{
    mLoadPlaylist = new KAction(tr("loadplaylist"), this);
    mLoadPlaylist->setText(tr("Load Playlist"));
    mLoadPlaylist->setObjectName("LoadPlaylist");
    mLoadPlaylist->setGlobalShortcut( KShortcut(), KAction::ActiveShortcut );
    connect(mLoadPlaylist,SIGNAL(triggered()),this,SLOT(loadPlaylist()));
    actionCollection()->addAction("LoadPlaylist",mLoadPlaylist);

    mPlayPause = new KAction(KIcon("media-playback-start"),tr("Play media"),this);
    mPlayPause->setText(tr("Play media"));
    mPlayPause->setIcon(KIcon("media-playback-start"));
    mPlayPause->setObjectName("PlayPause");
    mPlayPause->setGlobalShortcut( KShortcut( Qt::META + Qt::Key_MediaPlay ) );
//     mPlayPause->setGlobalShortcut( KShortcut(), KAction::ActiveShortcut );
    connect(mPlayPause,SIGNAL(triggered()),ui->playMedia,SLOT(click()));
    actionCollection()->addAction("PlayPauseMedia",mPlayPause);
    mNext = new KAction(KIcon("media-skip-forward"),tr("Next media"),this);
    mNext->setText(tr("Next media"));
    mNext->setIcon(KIcon("media-skip-forward"));
    mNext->setObjectName("NextMedia");
    mNext->setGlobalShortcut( KShortcut( Qt::META + Qt::Key_MediaNext ) );
    connect(mNext,SIGNAL(triggered()),ui->nextMedia,SLOT(click()));
    actionCollection()->addAction("NexMedia",mNext);
    mPrev = new KAction(KIcon("edia-skip-backward"),tr("Previous media"),this);
    mPrev->setText(tr("Previous media"));
    mPrev->setIcon(KIcon("media-skip-backward"));
    mPrev->setObjectName("PreviousMedia");
    mPrev->setGlobalShortcut( KShortcut( Qt::META + Qt::Key_MediaPrevious ) );
    actionCollection()->addAction("Previousmedia",mPrev);
    
    mStatusNotifierItem = new KStatusNotifierItem(this);
    mStatusNotifierItem->setCategory(KStatusNotifierItem::ApplicationStatus);
    mStatusNotifierItem->setToolTipTitle("PlaybaK");
    mStatusNotifierItem->setTitle("PlaybaK");
    mStatusNotifierItem->setIconByName("media-playback-start");
    mStatusNotifierItem->contextMenu()->addAction(mPlayPause);
    mStatusNotifierItem->contextMenu()->addAction(mNext);
    mStatusNotifierItem->contextMenu()->addAction(mPrev);
    //         mStatusNotifierItem->setContextMenu(contextMenu);

    // It adds the action in the menu bar, created on playbakui.rc model.
    KStandardAction::quit ( this, SLOT ( queryClose() ), actionCollection() );
//     KStandardAction::quit ( qApp, SLOT ( queryClose() ), actionCollection() );
    KStandardAction::preferences ( this, SLOT ( showSettingsDialog() ), actionCollection() );
    KStandardAction::keyBindings(this, SLOT(showShortcutsSettingsDialog()), actionCollection());
    createGUI("playbakui.rc");
    connect(this,SIGNAL(destroyed()),this,SLOT(closeAllWindows()));
//     setupGUI(Create | Keys);
    

}

void MainWindow::closeAllWindows(){
  if (QObject::sender() != 0x0L) {
    queryClose();
  }
}

bool MainWindow::queryClose() {
  return true;
//   if (QObject::sender() != 0x0L) {
//     return queryExit();
//   }
//   hide();
//   return false;
}

bool MainWindow::queryExit() {
//! TODO When exit from the aplication, we save the session
//   saveProperties(&kapp->sessionConfig()->group("PlaybaK"));
// saveProperties(&KGlobal::config().operator->()->group("PlaybaK"));

saveProperties(mGroup);
  return true;
}

void MainWindow::showShortcutsSettingsDialog() {
  KShortcutsDialog::configure(actionCollection());
//   KGlobalAccel::self()->activateGlobalShortcutContext(this->componentData().componentName(),"PlaybaK");
  actionCollection()->writeSettings();
  //NOTE No se debería pasar una variable propia? Porque se le está pasando un objeto temporal.
//   actionCollection()->exportGlobalShortcuts(&KGlobal::config()->group(actionCollection()->configGroup()));
  if (mGlobalConfig != 0x0L)
    actionCollection()->exportGlobalShortcuts(mGlobalConfig);
}

void MainWindow::addFiles(){
  QStringList files = KFileDialog::getOpenFileNames(KGlobalSettings::desktopPath(), "application/x-matroska video/mpeg-4 video/mpeg video/quicktime video/x-la-asf video/x-ms-asf audio/aac audio/ac3 audio/midi audio/mp3 audio/ogg audio/wav audio/x-scpls audio/x-mpegurl", this);
  QList<MediaItem*> partialMediaItemsList;
  int filesQuant = files.size();
  for(int i = 0; i < filesQuant; ++i)
    partialMediaItemsList.append(new MediaItem(files[i],true));

  mMediaItems.append(partialMediaItemsList);

  ui->playlist->addItems( &partialMediaItemsList );
}

void MainWindow::saveProperties( KConfigGroup *config) {
  QString entry;
  config->writeEntry( "items number", ui->playlist->count());
  for (int i = 0; i < ui->playlist->count();++i)  {
    entry = QString("item") + QString::number(i);
    config->writeEntry( entry, ui->playlist->mediaItem(i)->url().toLocalFile() );
  }
}

void MainWindow::readProperties(const KConfigGroup *config) {
  QString entry;
  QStringList items;
  int intemsNumber = config->readEntry("items number").toInt();
  for (int i = 0; i < intemsNumber;++i)  {
    entry = QString("item") + QString::number(i);
    items.append( config->readEntry( entry) );
  }

  //TODO
//   mPlaylistWidget->addItems(items);
}


MainWindow::~MainWindow()
{
  delete ui;
}
#include <mainwindow.moc>