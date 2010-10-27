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

#include "Ontologies.hpp"

#include <Nepomuk/ResourceManager>
#include <Nepomuk/Variant>
#include <Nepomuk/Types/Class>
#include <Nepomuk/Tag>
#include <Nepomuk/Resource>
#include <Nepomuk/Tag>

#include <taglib/fileref.h>
#include <taglib/tag.h>




// #include <Nepomuk/Resour1ceManager>
#include <Nepomuk/Resource>
#include <Nepomuk/Variant>

#include <Nepomuk/Tag>

#include "AudioMediaItem.hpp"

AudioMediaItem::AudioMediaItem(KUrl url) :
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
