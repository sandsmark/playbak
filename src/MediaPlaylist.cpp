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

MediaPlaylist::MediaPlaylist() :
  QObject()
{
  mMode = Mode::NORMAL;
  mCurrent = -1;
  mOutputWidget = 0x0l;
  mVideoPlayer = 0x0l;
}

MediaPlaylist::~MediaPlaylist()
{
}

void MediaPlaylist::play(int position){
  setCurrent(position);
  play();
}

void MediaPlaylist::setTick( int tick){
  mVideoPlayer->seek(tick);
}

MediaItem* MediaPlaylist::operator[](const int position)
{
  return mItemList[position];
}

void MediaPlaylist::addMediaItem(MediaItem* mediaItem)
{
  mItemList.append( mediaItem );
  if(mCurrent <  0){
    mCurrent = 0;
    QEventLoop loop;
    mVideoPlayer->play(Phonon::MediaSource(this->mediaItem()->url().toLocalFile()));
    connect(mVideoPlayer->mediaObject(), SIGNAL(stateChanged(Phonon::State,Phonon::State)),&loop,SLOT(quit()));
    mVideoPlayer->stop();
    loop.exec();
    emit trackChanged();
  }

  emit addedItem();
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

MediaPlaylist::Mode::MediaPlaylistMode MediaPlaylist::mode()
{
  return mMode;
}

qint64 MediaPlaylist::totalTime(){
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
  connect(mVideoPlayer->mediaObject(), SIGNAL(stateChanged(Phonon::State,Phonon::State)),&loop,SLOT(quit()));
  loop.exec();
  emit totalTime(int(mVideoPlayer->totalTime()));
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
  setCurrent(position);
}

void MediaPlaylist::selectNext()
{
  // FIXME:  En realidad depende del modo
  // Si avanzamos desde el ultimo, saltamos al primero
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
  
  emit trackChanged();
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

  emit trackChanged();
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
  emit trackChanged();
}

void MediaPlaylist::setCurrent(MediaItem* media)
{
  if ( (mCurrent = mItemList.indexOf(media)) < 0 )
    mCurrent = 0;
  emit trackChanged();
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
    mVideoPlayer = new Phonon::VideoPlayer(outputWidget);
    mVideoPlayer->mediaObject()->setTickInterval(100);
    connect(mVideoPlayer,SIGNAL(finished()),this,SLOT(playNext()));
    connect(mVideoPlayer->mediaObject(),SIGNAL(tick(qint64)),this,SIGNAL(tick(qint64)));
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