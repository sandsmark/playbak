/*
 *  The PlaybaK Multimedia Player's library.
 *  Copyright (C) 2010 PlaybaK Development Team (see AUTHORS file)
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

//TODO Cambiar el 'magic number = 100' por un valor en la configuración de PlaybaK, algo como 'progressBarStep'.

#include <MediaPlaylist.h>
#include <QEventLoop>
#include <AudioMediaItem.h>
#include <VideoMediaItem.h>
#include <PlaylistAudioItemWidget.h>
#include <PlaylistVideoItemWidget.h>
#include <qlabel.h>

#include <iostream>

MediaPlaylist::MediaPlaylist(QWidget* parent) :
  QWidget(parent)
{
  mMode = Mode::NORMAL;
  mMute = false;
  mCurrent = -1;
  mOutputWidget = 0x0l;
  mVideoPlayer = 0x0l;
  
//   steps = 250;

  mCanvas = new QWidget;
//   mCanvas->setStyleSheet("background:red;");
  
  mScrollBar = new QScrollBar;
  mScrollBar->setMaximum(0);
  mScrollBar->setMinimum(0);
  mScrollBar->setValue(0);
  mScrollBar->setPageStep(125);
  
  mLayout = new QHBoxLayout;
  this->setLayout(mLayout);
  mLayout->addWidget(mCanvas);
  mLayout->addWidget(mScrollBar);
  mLayout->setSpacing(0);
  mLayout->setContentsMargins(0,0,0,0);
//   this->set;
  
  connect(mScrollBar, SIGNAL(valueChanged(int)), this, SLOT(sincronizeWithScroll(int)));
}

MediaPlaylist::~MediaPlaylist()
{
}

void MediaPlaylist::play(int position){
  setCurrent(position);
  play();
}

void MediaPlaylist::setTick( int tick){
  mVideoPlayer->seek((qint64)tick);
}

MediaItem* MediaPlaylist::operator[](const int position)
{
  return mItemList[position];
}

void MediaPlaylist::addItems(QList<MediaItem*> *items)
{
  int parent_pos = mItemList.size();
  mItemList.append( *items );
  int i = 0;
  foreach(MediaItem *item, *items) {
    if (!item->mimetype().isEmpty()){
//       QListWidget::addItem(item->title());

      if (
            // Audio normal
            item->mimetype().contains("audio",Qt::CaseInsensitive) or
            // Streaming
            item->mimetype().contains("stream",Qt::CaseInsensitive) or
            item->mimetype().contains("mpegurl",Qt::CaseInsensitive) or
            item->mimetype().contains("octeta-stream",Qt::CaseInsensitive)
         )
      {
        int widgetPos = virtualHeight();
        AudioMediaItem *audioMediaItem = new AudioMediaItem(*item);
        PlaylistAudioItemWidget *widget = new PlaylistAudioItemWidget(*audioMediaItem,mCanvas);
        
        widget->move(0, widgetPos );
        widget->mParentChildPos = parent_pos;
        
        // Solo redimencionamos mCanvas cuando la altura virtual del playlist es mayor a su alto.
        if(virtualHeight() > mCanvas->size().height())
          mCanvas->resize(mCanvas->size().width(), virtualHeight());
        
        connect(widget, SIGNAL(resized(int)),
                this,   SLOT(updatePositionsFrom(int)));
        connect(widget, SIGNAL(play(int)),
                this,   SLOT(play(int)));
        connect(widget, SIGNAL(selected(int)),
                this,   SLOT(select(int)));
        
        // Adaptamos el scrollbar al tamaño virtual de la lista de reproducción. Ver virtualHeight()
        if ((virtualHeight() - this->size().height()) > 0)
          mScrollBar->setMaximum(virtualHeight() - mScrollBar->size().height());
        else
          mScrollBar->setMaximum(0);
      
        widget->show();
      }
      else if (item->mimetype().contains("video",Qt::CaseInsensitive))
      {
        int widgetPos = virtualHeight();
        VideoMediaItem *videoMediaItem = new VideoMediaItem(*item);
        PlaylistVideoItemWidget *widget = new PlaylistVideoItemWidget(*videoMediaItem, mCanvas);
        
        widget->move(0, widgetPos );
        widget->mParentChildPos = parent_pos;
        
        if(virtualHeight() > mCanvas->size().height())
          mCanvas->resize(mCanvas->size().width(), virtualHeight());
        
        connect(widget, SIGNAL(resized(int)),
                this,   SLOT(updatePositionsFrom(int)));
        connect(widget, SIGNAL(play(int)),
                this,   SLOT(play(int)));
        
        if ((virtualHeight() - this->size().height()) > 0)
          mScrollBar->setMaximum(virtualHeight() - mScrollBar->size().height());
        else
          mScrollBar->setMaximum(0);
      
        widget->show();
        

      }
      ++i;
    }
    qDebug("parentpos: " + QString::number(parent_pos).toAscii());
    ++parent_pos;
  }
  
  if(mCurrent <  0){
    mCurrent = 0;
    QEventLoop loop;
    mVideoPlayer->play(Phonon::MediaSource(this->mediaItem()->url().toLocalFile()));
    connect(mVideoPlayer->mediaObject(), SIGNAL(stateChanged(Phonon::State,Phonon::State)),&loop,SLOT(quit()));
    mVideoPlayer->stop();
    loop.exec();
  }
}

void MediaPlaylist::keyPressEvent(QKeyEvent *e){
  qDebug("Press");
  if (e->key() | Qt::Key_Shift)
    mKeyShiftPressed = true;
  if (e->key() | Qt::Key_Control)
    mKeyShiftPressed = true;
}

void MediaPlaylist::keyReleaseEvent(QKeyEvent *e){
  if (e->key() | Qt::Key_Shift)
    mKeyShiftPressed = false;
  if (e->key() | Qt::Key_Control)
    mKeyShiftPressed = false;
}

void MediaPlaylist::removeItem(int position){
//   If the item is out of the range, we do nothing
  if ( ( position < 0 ) ||
       ( position > mCanvas->children().size()) )
    return;
  PlaylistAbstractMediaItem *w;
  /*
   * Si es el primer elemento el que hay que mover y su posición es mayor o igual a cero,
   * movemos el elemento para arriba (la posición 0,0), solo movemos el siguiente, si hay siguiente
   */
  if ((position == 0) && (mCanvas->children().size() > 1)) {
    w = qobject_cast< PlaylistAbstractMediaItem* >(mCanvas->children().at(1));
    w->move(0,0);
  }
  w = static_cast<PlaylistAbstractMediaItem*>(mCanvas->children().at(position));
  QPoint p = w->pos();
  w->setParent(0x0L);
  w->destroy();
  mItemList.removeAt(position);

  updatePositionsFrom(0);
}

void MediaPlaylist::removeSelecteds()
{
  if (  mCanvas->children().size() == 0 )
    return;
  QObject *item;
  int remove_count = 0;
  foreach(item, mCanvas->children())
  {
    PlaylistItemWidget *l_item;
    if ( l_item = qobject_cast< PlaylistItemWidget* >(item))
      if (l_item->getSelected()){
        removeItem(l_item->mParentChildPos);
        remove_count++;
      }
      else {
        l_item->mParentChildPos -= remove_count;
      }
      
  }
}


void MediaPlaylist::updatePositionsFrom(int position)
{
  if ( ( position < 0 ) ||
       ( position > mCanvas->children().size()) )
    return;
  QWidget *item = 0x0L;
  int actual = 0;
  QWidget *lastChild = 0x0L;
  foreach(QObject* object, mCanvas->children()){
    if (0 < position < actual){
      item = qobject_cast< QWidget* >(object);
      item->move(0, lastChild->pos().y() + lastChild->height() );
    }
    lastChild = qobject_cast< QWidget* >(object);
    actual++;
  }
  
  // Solo redimencionamos mCanvas cuando la altura virtual del playlist es mayor a su alto.
  if(virtualHeight() > mCanvas->size().height())
    mCanvas->resize(mCanvas->size().width(), virtualHeight());
  
  // Actualizamos el tamaño del scrollbar
  if ((virtualHeight() - this->size().height()) > 0)
    mScrollBar->setMaximum(virtualHeight() - mScrollBar->size().height());
  else
    mScrollBar->setMaximum(0);
}

void MediaPlaylist::sincronizeWithScroll(int value)
{
  mCanvas->move(mCanvas->pos().x(),-mScrollBar->value());
}


void MediaPlaylist::resizeEvent(QResizeEvent *) {
  QWidget *child = 0x0L;
  foreach(QObject* object, mCanvas->children()){
    child = qobject_cast< QWidget* >(object);
    child->resize(mCanvas->width(), child->height());
  }
  
  // Actualizamos el tamaño del scrollbar
  if ((virtualHeight() - this->size().height()) > 0)
    mScrollBar->setMaximum(virtualHeight() - mScrollBar->size().height());
  else
    mScrollBar->setMaximum(0);
  
  // Solo redimencionamos mCanvas cuando la altura virtual del playlist es mayor a su alto.
  if(virtualHeight() > mCanvas->size().height())
    mCanvas->resize(mCanvas->size().width(), virtualHeight());
}

// El tamaño virtual del playlist es 'la posición y del último item + su altura'.
int MediaPlaylist::virtualHeight()
{
  if(!mCanvas->children().size())
    return 0;
  QWidget *lastChild = qobject_cast< QWidget* >(mCanvas->children().last());
  return lastChild->pos().y() + lastChild->size().height();
}

int MediaPlaylist::count()
{
  return mItemList.count();
}

int MediaPlaylist::current()
{
  return mCurrent;
}

MediaItem* MediaPlaylist::mediaItem()
{
  if ( (mCurrent >= mItemList.count()) || (mCurrent < 0) )
    return 0x0L;
  
  return mItemList[mCurrent];
}

MediaItem* MediaPlaylist::mediaItem(const int position)
{
  return mItemList[position];
}

Phonon::MediaObject* MediaPlaylist::mediaObject()
{
  if (mVideoPlayer)
    return mVideoPlayer->mediaObject();
  return 0x0L;
}

MediaPlaylist::Mode::MediaPlaylistMode MediaPlaylist::mode()
{
  return mMode;
}

qint64 MediaPlaylist::currentTotalTime(){
  return mVideoPlayer->totalTime();
}

void MediaPlaylist::insert(int position, MediaItem* mediaItem)
{
  mItemList.insert(position, mediaItem);
}

void MediaPlaylist::move(int from, int to)
{
  mItemList.move(from, to);
}

void MediaPlaylist::remove(MediaItem* mediaItem)
{
  mItemList.removeAll(mediaItem);
}

void MediaPlaylist::remove(const int position)
{
  mItemList.removeAt(position);
}

void MediaPlaylist::setVolume(qreal volume){
  if (mVideoPlayer == 0x0L)
    return;

  if (volume > 1.0)
    volume = 1.0;
  else if (volume < 0.0)
    volume = 0.0;
  mVolume = (int)(volume * 100.0);
  if(!isMute())
    mVideoPlayer->setVolume(volume);
}
void MediaPlaylist::play()
{
  if ( (mVideoPlayer == 0x0l) || (mCurrent < 0) )
    return;

  if (mVideoPlayer->isPlaying() | mVideoPlayer->isPaused())
    mVideoPlayer->stop();

  QEventLoop loop;
  mVideoPlayer->play(Phonon::MediaSource(mediaItem()->url().toLocalFile()));

  //! This value is Ok. A lower value make the application slower. 500 is Ok too.
  mVideoPlayer->mediaObject()->setTickInterval(1000);
  connect(mVideoPlayer->mediaObject(), SIGNAL(stateChanged(Phonon::State,Phonon::State)),&loop,SLOT(quit()));
  loop.exec();
//   emit totalTime(mVideoPlayer->totalTime());
  emit trackChanged();
}

void MediaPlaylist::playNext() {
  selectNext();
  play();  
}

void MediaPlaylist::playPrevious() {
  selectPrevious();
  play();
}

void MediaPlaylist::pause()
{
  if (mVideoPlayer == 0x0l)
    return;
  if (mVideoPlayer->isPlaying())
    mVideoPlayer->pause();
}

void MediaPlaylist::playPause()
{
  if ( (mVideoPlayer == 0x0l) || (mCurrent < 0) )
    return;

  if (mVideoPlayer->isPlaying())
    mVideoPlayer->pause();
  else{
    if(mVideoPlayer->mediaObject()->currentSource().url() == QUrl())
      play();
    else
      mVideoPlayer->play();
  }
  
}

void MediaPlaylist::select(const int position)
{
  PlaylistAbstractMediaItem *item = 0x0L;
  if(!mKeyControlPressed){
    foreach(QObject *object, mCanvas->children()) {
      item = qobject_cast< PlaylistAbstractMediaItem* >(object);
      item->setSelected(false);
    }
  }
  item = qobject_cast< PlaylistAbstractMediaItem* >(mCanvas->children().at(position));
  item->setSelected(true);
}

void MediaPlaylist::selectNext()
{
  if (mItemList.count() == 0)
  {
    mCurrent = -1;
    return;
  }
  if (mMode == Mode::LOOP_PLAYLIST){
    if ( ++mCurrent >= mItemList.count() )
      mCurrent = 0;
    
  } else if (mMode == Mode::NORMAL) {
    if ( ++mCurrent >= mItemList.count() )
      mCurrent = -1;
  } else if (mMode == Mode::LOOP_MEDIA) {
      return;
  } else if (mMode == Mode::SHUFFLE_ALL) {
    mCurrent = qrand() %  mItemList.count();      
  }
  
//   emit trackChanged();
}

void MediaPlaylist::selectPrevious()
{
  if (mItemList.count() == 0)
  {
    mCurrent = -1;
    return;
  }
  
  if (mMode == Mode::LOOP_PLAYLIST){
    if ( --mCurrent <  0 )
      mCurrent = mItemList.count() - 1;
    
  } else if (mMode == Mode::NORMAL) {
    if ( --mCurrent < 0 )
      mCurrent = 0;
  } else if (mMode == Mode::LOOP_MEDIA) {
      return;
  } else if (mMode == Mode::SHUFFLE_ALL) {
    mCurrent = qrand() %  mItemList.count();
  }

//   emit trackChanged();
}

bool MediaPlaylist::isMute()
{
  return mMute;
}

void MediaPlaylist::setCurrent(const int current)
{
  // Si la canción no existe, seleccionamos el primero
  if ((mCurrent = current) > mItemList.count())
    mCurrent = 0;
//   emit trackChanged();
}

void MediaPlaylist::setCurrent(MediaItem* media)
{
  if ( (mCurrent = mItemList.indexOf(media)) < 0 )
    mCurrent = 0;
//   emit trackChanged();
}

void MediaPlaylist::setMode(const Mode::MediaPlaylistMode mode)
{
  mMode = mode;
}

void MediaPlaylist::setMute(const bool mute)
{
  mMute = mute;
  if(mute)
    mVideoPlayer->setVolume(0.0);
  else
    mVideoPlayer->setVolume((qreal)(mVolume)/100.0);
}

void MediaPlaylist::setOutputWidget(QWidget *outputWidget)
{
  if (!mVideoPlayer){
    mVideoPlayer = new Phonon::VideoPlayer(Phonon::VideoCategory,outputWidget);
    mVideoPlayer->mediaObject()->setTickInterval(100);
    connect(mVideoPlayer,SIGNAL(finished()),this,SLOT(playNext()));
    connect(mVideoPlayer->mediaObject(),SIGNAL(tick(qint64)),this,SIGNAL(tick(qint64)));
    connect(mVideoPlayer->mediaObject(), SIGNAL(totalTimeChanged(qint64)),this, SIGNAL(totalTime(qint64)));
//     connect(mVideoPlayer->mediaObject(), SIGNAL(currentSourceChanged(Phonon::MediaSource)),this, SIGNAL(trackChanged()));
  }
}

int MediaPlaylist::volume()
{
  return mVolume;
}

Phonon::State MediaPlaylist::state(){
  if(mVideoPlayer == 0x0L)
    return Phonon::ErrorState;
  return mVideoPlayer->mediaObject()->state();
}

#include "../include/MediaPlaylist.moc"