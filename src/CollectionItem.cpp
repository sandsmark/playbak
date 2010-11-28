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

#include <QPixmap>

#include <CollectionItem.h>

CollectionItem::Category::CollectionItemCategory CollectionItem::category()
{
  return mCategory;
}

QPixmap* CollectionItem::thumbnail()
{
  if (mThumbnail.isEmpty())
    return 0x0l;
  return new QPixmap(mThumbnail.toLocalFile());
}

CollectionItem::Type::CollectionItemType CollectionItem::type()
{
  return mType;
}

void CollectionItem::setCategory(Category::CollectionItemCategory category)
{
  mCategory = category;
  // TODO: Save in Nepomuk
}

void CollectionItem::setThumbnail(KUrl thumbnail)
{
  mThumbnail = thumbnail;
}

void CollectionItem::setType(Type::CollectionItemType type)
{
  mType = type;
}

CollectionItem::CollectionItem(Type::CollectionItemType type) :
  QObject(),
  mType(type),
  mCategory(Category::NONE) //TODO: Temporal
{
}