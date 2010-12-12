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

#ifndef PLAYBAK_COMPOSEDMEDIAITEMDATA_H
#define PLAYBAK_COMPOSEDMEDIAITEMDATA_H

// #include <QObject>
#include <QString>

#include <KDE/KUrl>

class ComposedMediaItemData
{
  protected:
    //! The composed media item's composer.
    /**
     * Nepomuk direction:
     *  nid3:composer: http://www.semanticdesktop.org/ontologies/nid3/#composer
     * ID3:
     *  TCOM
     */
    QString mComposer;
  public:
    //! Returns the composed media item's composer.
    QString composer();
  public:
    //! Set the composed media item's composer.
    /*!
     * Need be overloaded because the file name is in MediaItem
     * \param composer the compositor's name.
     */
    virtual void setComposer(QString composer) = 0;
  public:
    ComposedMediaItemData(KUrl file);
};

#endif //PLAYBAK_COMPOSEDMEDIAITEMDATA_H
 
