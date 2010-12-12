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

#include <taglib/fileref.h>
#include <taglib/tag.h>

#include <QEventLoop>
#include <QThread>

#include <Nepomuk/Resource>
#include <Nepomuk/ResourceManager>
#include <Nepomuk/Tag>
#include <Nepomuk/Types/Class>
#include <Nepomuk/Variant>

#include <AudioMediaItem.h>
#include <Ontologies.h>

AudioMediaItem::AudioMediaItem(const MediaItem& copy_mediaitem):
MediaItem(copy_mediaitem),
AlbumMediaItemData(mUrl),
ArtisticalMediaItemData(mUrl),
ComposedMediaItemData(mUrl),
PlayableMediaItemData(mUrl)
{
  // TODO: Read from nepomuk the subtype (we need create own ontology)
  mSubtype = AudioMediaItem::Subtype::NORMAL;
//   if (metadataObserver != 0x0L) {
//     connect(metadataObserver,SIGNAL(metaDataChanged()),this,SLOT(loadAudioMediaItemMetadata()));
//   }
//   AudioMediaItemConstructor *c = new AudioMediaItemConstructor(this);
//   c->start();
  firstConstructAudioMediaItem();
}

AudioMediaItem::AudioMediaItem(const AudioMediaItem& copy):
MediaItem(copy),
AlbumMediaItemData(mUrl),
ArtisticalMediaItemData(mUrl),
ComposedMediaItemData(mUrl),
PlayableMediaItemData(mUrl)
{
  // TODO: Read from nepomuk the subtype (we need create own ontology)
  mSubtype = AudioMediaItem::Subtype::NORMAL;
//   if (metadataObserver != 0x0L) {
//     connect(metadataObserver,SIGNAL(metaDataChanged()),this,SLOT(loadAudioMediaItemMetadata()));
//   }
//   AudioMediaItemConstructor *c = new AudioMediaItemConstructor(this);
//   c->start();
  firstConstructAudioMediaItem();
}


AudioMediaItem::AudioMediaItem(KUrl url, bool byDemand) :
  MediaItem(url,byDemand),
  AlbumMediaItemData(url),
  ArtisticalMediaItemData(url),
  ComposedMediaItemData(url),
  PlayableMediaItemData(url)
{
  mTrackNumber = 0;
  AudioMediaItemConstructor *c = new AudioMediaItemConstructor(this);
  c->start();
}

void AudioMediaItem::firstConstructAudioMediaItem()
{
  // TODO: Read from nepomuk the subtype (we need create own ontology)
  mSubtype = AudioMediaItem::Subtype::NORMAL;
//   if (metadataObserver != 0x0L) {
//     QEventLoop loop;
//     QObject::connect(metadataObserver, SIGNAL(stateChanged(Phonon::State,Phonon::State)), &loop, SLOT(quit()));
//     loop.exec();
//     connect(metadataObserver,SIGNAL(metaDataChanged()),this,SLOT(loadAudioMediaItemMetadata()));
//   }
  if (mByDemand == false)
  {
    loadAudioMediaItemMetadata();
  }
//   disconnect(this,SIGNAL(constructAudioMediaItem()),0,0);
}

void AudioMediaItem::loadAudioMediaItemMetadata() {

  /* If is by demand, MediaItem construct the necesaries pointers, else
   * we create the pointers if are not seted
   */
  if (mByDemand){
    // We wait to MediaItem to construct the rFile (and etc.) object
    while (rFile == 0x0L){}
  }
  else
  {
    if (rFile == 0x0L)
      rFile = new Nepomuk::Resource(mUrl);;
    if (variant == 0x0L)
      variant = new Nepomuk::Variant;;
    if (id3File == 0x0L)
      id3File = new TagLib::FileRef(mUrl.toLocalFile().toUtf8());;
  }

      
  // We verity is Nepomuk was initialized (is recomended if we use thread, and we use it)
  if (rFile->manager()->initialized())
    rFile->manager()->init();

  // PlayableMediaItemData Metadata
  if ((id3File->audioProperties() != 0x0L) && (id3File->audioProperties()->length() != 0) ) {
    int h, m, s;
    h = id3File->audioProperties()->length()/60/60;
    m = (id3File->audioProperties()->length()/60) - (h * 60);
    s = id3File->audioProperties()->length() - ((m * 60) + (h*60*60));
    mDuration =QTime(h,m,s);
    
  } else if ( rFile->hasProperty(NID3_LENGHT) )
  {
    *variant = rFile->property(NID3_LENGHT);
    mDuration = variant->toTime();
  } else if ( rFile->hasProperty(XESAM_MEDIADURATION) )
  {
    *variant = rFile->property(XESAM_MEDIADURATION);
    mDuration = variant->toTime();
  }

  if ((id3File->tag() != 0x0L) && (!id3File->tag()->genre().isEmpty()))
    mGenre = id3File->tag()->genre().toCString();
  else if ( (*variant = rFile->property(NID3_CONTENTTYPE)).isValid() )
    mGenre = variant->toString();
//   else
//     mGenre = id3File->tag()->genre().toCString();

  if ( (*variant = rFile->property(NID3_INVOLVEDPERSONS)).isValid() )
    mInvolvedPersons = variant->toStringList();

  if ( (*variant = rFile->property(NID3_LANGUAGE)).isValid() )
    mLanguage = variant->toString();
  else if ( (*variant = rFile->property(NIE_LANGUAGE)).isValid() )
    mLanguage = variant->toString();

  mStartat = 0;

  // AlbumMediaItemData Metadata
  if ((id3File->tag() != 0x0L) && (!id3File->tag()->album().isEmpty()))
    mAlbum = id3File->tag()->album().toCString();
  else if ( (*variant = rFile->property(NID3_ALBUMTITLE)).isValid() )
    mAlbum = variant->toString();
  else if ( (*variant = rFile->property(NID3_ORIGINALALBUMTITLE)).isValid() )
    mAlbum = variant->toString();
  else if ( (*variant = rFile->property(XESAM_ALBUM)).isValid() )
    mAlbum = variant->toString();

  if ((id3File->tag() != 0x0L) && (id3File->tag()->track() != 0))
    mTrackNumber = id3File->tag()->track();
  else if ( (*variant = rFile->property(NID3_TRACKNUMBER)).isValid() )
    mTrackNumber = variant->toInt();
//   else
//     mTrackNumber = id3File->tag()->track();

  // ArtisticalMediaItemData Metadata
  if ((id3File->tag() != 0x0L) && (!id3File->tag()->artist().isEmpty()))
    mArtist = id3File->tag()->artist().toCString();
  else if ( (*variant = rFile->property(NID3_ORIGINALARTIST)).isValid() )
    mArtist = variant->toString();
  else if ( (*variant = rFile->property(NIE_LEADERARTIST)).isValid() )
    mArtist = variant->toString();
  else if ( (*variant = rFile->property(NEXIF_ARTIST)).isValid() )
    mArtist = variant->toString();
  else if ( (*variant = rFile->property(XESAM_ARTIST)).isValid() )
    mArtist = variant->toString();

  // ComposedMediaItemData Metadata
  if ( (*variant = rFile->property(XESAM_COMPOSER)).isValid() )
    mComposer = variant->toString();
  
  emit metadataChanged();

  // When we load all metadatas, is no more necesary use mByDemand
  mByDemand = false;
  delete rFile;
  delete variant;
  delete id3File;
  rFile = 0x0L;
  variant = 0x0L;
  id3File = 0x0L;
}

void AudioMediaItem::setSubtype(Subtype::AudioMediaItemSubtype subtype)
{
  mSubtype = subtype;
  // TODO: Save in nepomuk this data (we need create own ontology)
}

AudioMediaItem::Subtype::AudioMediaItemSubtype AudioMediaItem::subtype()
{
  return mSubtype;
}

QTime AudioMediaItem::duration(){
  if (mByDemand && mDuration.isNull())
  {
    if ((id3File->audioProperties() != 0x0L) && (id3File->audioProperties()->length() != 0) ) {
      int h, m, s;
      h = id3File->audioProperties()->length()/60/60;
      m = (id3File->audioProperties()->length()/60) - (h * 60);
      s = id3File->audioProperties()->length() - ((m * 60) + (h*60*60));
      mDuration =QTime(h,m,s);
      
    } else if ( rFile->hasProperty(NID3_LENGHT) )
    {
      while ((variant == 0x0L) || (rFile == 0x0L))
        ;
      *variant = rFile->property(NID3_LENGHT);
      mDuration = variant->toTime();
    } else if ( rFile->hasProperty(XESAM_MEDIADURATION) )
    {
      while ((variant == 0x0L) || (rFile == 0x0L))
        ;
      *variant = rFile->property(XESAM_MEDIADURATION);
      mDuration = variant->toTime();
    }
  }
  return mDuration;
}

QString AudioMediaItem::genre() {
  if (mByDemand && mGenre.isEmpty())
  {
    if ((id3File->tag() != 0x0L) && (!id3File->tag()->genre().isEmpty()))
      mGenre = id3File->tag()->genre().toCString();
    else if ( (*variant = rFile->property(NID3_CONTENTTYPE)).isValid() )
      mGenre = variant->toString();
//     else
//       mGenre = id3File->tag()->genre().toCString();
  }
  return mGenre;
}

QStringList AudioMediaItem::involvedPersons(){
  if (mByDemand && mInvolvedPersons.isEmpty())
  {
    if ( (*variant = rFile->property(NID3_INVOLVEDPERSONS)).isValid() )
      mInvolvedPersons = variant->toStringList();
  }
  return mInvolvedPersons;
}

QString AudioMediaItem::language(){
  if (mByDemand && mLanguage.isEmpty())
  {
    if ( (*variant = rFile->property(NID3_LANGUAGE)).isValid() )
      mLanguage = variant->toString();
    else if ( (*variant = rFile->property(NIE_LANGUAGE)).isValid() )
      mLanguage = variant->toString();
  }
  return mLanguage;
}

QString AudioMediaItem::album() {
  if (mByDemand && mAlbum.isEmpty())
  {
    mAlbum = id3File->tag()->album().toCString();
    if (mAlbum.isEmpty())
      if ((id3File->tag() != 0x0L) && (!id3File->tag()->album().isEmpty()))
        mAlbum = id3File->tag()->album().toCString();
      else if ( (*variant = rFile->property(NID3_ALBUMTITLE)).isValid() )
        mAlbum = variant->toString();
      else if ( (*variant = rFile->property(NID3_ORIGINALALBUMTITLE)).isValid() )
        mAlbum = variant->toString();
      else if ( (*variant = rFile->property(XESAM_ALBUM)).isValid() )
        mAlbum = variant->toString();
  }
  return mAlbum;
}

int AudioMediaItem::trackNumber() {
  if (mByDemand && (mTrackNumber == 0))
  {
    if ((id3File->tag() != 0x0L) && (id3File->tag()->track() != 0))
      mTrackNumber = id3File->tag()->track();
    else if ( (*variant = rFile->property(NID3_TRACKNUMBER)).isValid() )
      mTrackNumber = variant->toInt();
//     else
//       mTrackNumber = id3File->tag()->track();
  }
  return mTrackNumber;
}

QString AudioMediaItem::composer() {
  if (mByDemand && mComposer.isEmpty())
  {
    if ( (*variant = rFile->property(XESAM_COMPOSER)).isValid() )
      mComposer = variant->toString();
  }
  return mComposer;
}

#include "AudioMediaItem.moc"