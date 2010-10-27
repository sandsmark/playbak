
#include "Collection.hpp"

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