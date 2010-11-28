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

#ifndef PLAYBAK_COLLECTIONITEM_H 
#define PLAYBAK_COLLECTIONITEM_H

#include <QList>
#include <QObject>

#include <KDE/KUrl>

//! The collection's item's class.
class CollectionItem : public QObject
{
  public:
    struct Category
    {
      //! The collection item's categories.
      /*!
       * TODO Complete the list.
       */
      enum CollectionItemCategory
      {    
        NONE = 0,
        ANIME,  /*!< Anime category. */
        MOVIE,  /*!< Movie category. */
        TVSERIE /*!< TV' serie category. */
      };
    };
    
    struct Type
    {
      //! The collection item's types.
      enum CollectionItemType
      {
        IMAGES = 0, /*!< Image type. */
        AUDIOS,     /*!< Audio type. */
        VIDEOS,     /*!< Video type. */
        MIX         /*!< Mix type. */
      };
    };
  private:
    //! The collection item's category.
    Category::CollectionItemCategory mCategory;
    
    //! The collection item's thumbnail's url.
    KUrl mThumbnail;
    
    //! The collection item's type.
    Type::CollectionItemType mType;
  public:
    //! Return the collection item's category.
    Category::CollectionItemCategory category();
    
    //! Return the collection item's thumbnail.
    /*!
     * If hasn't return 0x0L.
     */
    QPixmap* thumbnail();
    
    //! Return the collection item's type.
    Type::CollectionItemType type();
  public:
    //! Set the collection item's category.
    /*!
     * \param category the collection item's category.
     */
    void setCategory(Category::CollectionItemCategory category);
    
    //! Set the collection item's category.
    /*!
     * \param thumbnail the collection items's thumbnail's url.
     */
    void setThumbnail(KUrl thumbnail);
    
    //! Set the collection item's category.
    /*!
     * \param type the collection item's type.
     */
    void setType(Type::CollectionItemType type);
  public:
    CollectionItem(Type::CollectionItemType type);
};

#endif //PLAYBAK_COLLECTIONITEM_H
