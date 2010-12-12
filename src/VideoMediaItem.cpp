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
