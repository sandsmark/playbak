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

#include <Collection.h>

QList<CollectionItem*> Collection::childs()
{
  return mChilds;
}

QString Collection::name()
{
  return mName;
}

QList<Collection*> Collection::parents()
{
  return mParents;
}

void Collection::addChild(CollectionItem* child)
{
  if (!mChilds.contains(child))
    mChilds.append(child);
    // TODO: Save in Nepomuk
}

void Collection::addParent(Collection* parent)
{
  if (!mParents.contains(parent))
    mParents.append(parent);
    // TODO: Save in Nepomuk
}

void Collection::removeChild(CollectionItem* child)
{
  // NOTE: Is imposible have more than one pointer to same, the addChild verify that
  mChilds.removeOne(child);
  // TODO: Remove from Nepomuk
}

void Collection::removeParent(Collection* parent)
{
  // NOTE: Is imposible have more than one pointer to same, the addParent verify that
  mParents.removeOne(parent);
}

void Collection::setName(QString name)
{
  mName = name;
}