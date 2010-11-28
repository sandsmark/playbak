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

#include <Nepomuk/Resource>
#include <Nepomuk/ResourceManager>
#include <Nepomuk/Tag>
#include <Nepomuk/Types/Class>
#include <Nepomuk/Variant>

#include <AudioMediaItem.h>
#include <Ontologies.h>

AudioMediaItem::AudioMediaItem(KUrl url) :
  AlbumMediaItemData(url),
  ArtisticalMediaItemData(url),
  ComposedMediaItemData(url),
  PlayableMediaItemData(url),
  MediaItem(url)
{
  // TODO: Read from nepomuk the subtype (we need create own ontology)
  mSubtype = AudioMediaItem::Subtype::NORMAL;
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
