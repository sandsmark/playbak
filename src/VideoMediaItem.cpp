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

#include <VideoMediaItem.h>

#include <Nepomuk/Resource>
#include <Nepomuk/ResourceManager>
#include <Nepomuk/Tag>
#include <Nepomuk/Types/Class>
#include <Nepomuk/Variant>

VideoMediaItem::VideoMediaItem(const MediaItem& copy_mediaitem):
  MediaItem(copy_mediaitem),
  PlayableMediaItemData(copy_mediaitem.url()),
  VisualMediaItemData(copy_mediaitem.url())
{
  mSubtype = VideoMediaItem::Subtype::PERSONAL;
  if (mByDemand == false)
    loadVideoMediaItemMetadata();
}

VideoMediaItem::VideoMediaItem(const VideoMediaItem& copy):
  MediaItem(copy),
  PlayableMediaItemData(copy.mUrl),
  VisualMediaItemData(copy.mUrl)
{
  mSubtype = VideoMediaItem::Subtype::PERSONAL;
  if (mByDemand == false)
    loadVideoMediaItemMetadata();
}


VideoMediaItem::VideoMediaItem(KUrl url, bool byDemand) :
  MediaItem(url, byDemand),
  PlayableMediaItemData(url),
  VisualMediaItemData(url)
{
  mSubtype = VideoMediaItem::Subtype::PERSONAL;
  if (mByDemand == false)
    loadVideoMediaItemMetadata();
}

void VideoMediaItem::loadVideoMediaItemMetadata() {
  /*!
   * If is by demand, MediaItem construct the necessaries pointers, else
   * create the pointers if are not created.
   */
  if (rFile == 0x0L)
    rFile = new Nepomuk::Resource(mUrl);;
  if (variant == 0x0L)
    variant = new Nepomuk::Variant;
  if (id3File == 0x0L)
    id3File = new TagLib::FileRef(mUrl.toLocalFile().toUtf8());;

  //! Because is on demand we don't load nothing
  if (mByDemand)
    return;

  emit metadataChanged();

  delete rFile;
  delete variant;
  delete id3File;

  rFile = 0x0L;
  variant = 0x0L;
  id3File = 0x0L;
  //! When we load all metadatas, is no more necessary use mByDemand.
  mByDemand = false;
}

QString VideoMediaItem::editor()
{
  return mEditor;
}

QString VideoMediaItem::producer()
{
  return mProducer;
}

VideoMediaItem::Subtype::VideoMediaItemtype VideoMediaItem::subtype()
{
  return mSubtype;
}

QString VideoMediaItem::tagline()
{
  return mTagline;
}

void VideoMediaItem::setEditor(QString editor)
{
  // TODO
}

void VideoMediaItem::setProducer(QString producer)
{
  // TODO
}

void VideoMediaItem::setSubtype(VideoMediaItem::Subtype::VideoMediaItemtype subtype)
{
  // TODO
}

void VideoMediaItem::setTagline(QString tagline)
{
  // TODO
}

