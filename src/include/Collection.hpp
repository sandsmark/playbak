/*
    The PlaybaK Multimedia Player's library.
    Copyright (C) 2010 PlaybaK Development Team (see AUTHORS file)
    
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef PLAYBAK_COLLECTION_H 
#define PLAYBAK_COLLECTION_H

#include "CollectionItem.hpp"

#include <QList>
#include <QString>

//! The collection's class.
class Collection : public CollectionItem
{
  private:
    //! The collection's childs.
    QList<CollectionItem*> mChilds;
    
    //! The collection's name.
    QString mName;
    
    //! The collection's parents.
    /*!
     * A Collection may be child of various collection parents.
     * For example:
     * A OST collection may be in the specific OST's serie collection,
     * at the same time in the 'My favorites OST's' collection.
     */
    QList<Collection*> mParents;
  public:
    //! Return the collection's childs.
    QList<CollectionItem*> childs();
    
    //! Return the collection's name.
    QString name();
    
    //! Return the collection's parents.
    /*!
     * A Collection may be child of various collection parents.
     * For example:
     * A OST collection may be in the specific OST's serie collection,
     * at the same time in the 'My favorites OST's' collection.
     */
    QList<Collection*> parents();
  public:
    //! Add a child to collection.
    /*!
     * \param child the collection's category.
     */
    void addChild(CollectionItem* child);
    
    //! Add a parent to collection.
    /*!
     * \param parent the collection's parent.
     */
    void addParent(Collection* parent);
  public:
    //! Remove a child from collection.
    /*!
     * \param child the collection's child.
     */
    void removeChild(CollectionItem* child);
    
    //! Remove a parent collection.
    /*!
     * \param parent the collection's parent.
     */
    void removeParent(Collection* parent);
  public:    
    //! Set the collection's name.
    /*!
     * \param name the collection's name.
     */
    void setName(QString name);
  
};

#endif //PLAYBAK_COLLECTION_H
