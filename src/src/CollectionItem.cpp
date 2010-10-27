#include <QPixmap>
#include "CollectionItem.hpp"

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
  mType(type),
  mCategory(Category::NONE)
{
}