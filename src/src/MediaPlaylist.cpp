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

#include "MediaPlaylist.hpp"

MediaPlaylist::MediaPlaylist()
{
  mMode = Mode::NORMAL;
  mCurrent = -1;
}

MediaPlaylist::~MediaPlaylist()
{
}

MediaItem* MediaPlaylist::operator[](const int position)
{
  return mItemList[position];
}

void MediaPlaylist::addMediaItem(MediaItem* mediaItem)
{
  mItemList.append( mediaItem );
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

void MediaPlaylist::select(const int position)
{
  setCurrent(position);
}

void MediaPlaylist::selectNext()
{
  // FIXME:  En realidad depende del modo
  // Si avanzamos desde el ultimo, saltamos al primero
  if ( ++mCurrent >= mItemList.count() )
    mCurrent = 0;
}

void MediaPlaylist::selectPrevious()
{
  // FIXME:  En realidad depende del modo
  // TODO: Leer el historial
  // Si retrocedemos desde el primero, saltamos al ultimo
  if ( --mCurrent < 0 )
    mCurrent = mItemList.count() - 1;
}

void MediaPlaylist::setCurrent(const int current)
{
  // Si la canción no existe, seleccionamos el primero
  if ((mCurrent = current) > mItemList.count())
    mCurrent = 0;
}

void MediaPlaylist::setCurrent(MediaItem* media)
{
  if ( (mCurrent = mItemList.indexOf(media)) < 0 )
    mCurrent = 0;
}

void MediaPlaylist::setMode(const Mode::MediaPlaylistMode mode)
{
  mMode = mode;
}