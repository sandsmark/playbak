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

#ifndef PLAYBAK_ALBUMMEDIAITEMDATA_H
#define PLAYBAK_ALBUMMEDIAITEMDATA_H

#include <QString>

#include <MediaItem.h>

class AlbumMediaItemData
{
  private:
    //! The album media item's album's name.
    /**
     * Nepomuk direction:
     *  nid3:albumTitle: http://www.semanticdesktop.org/ontologies/nid3/#albumTitle
     *  nid3:originalAlbumTitle: http://www.semanticdesktop.org/ontologies/nid3/#originalAlbumTitle
     * ID3:
     *  TALB (Album/Movie/Show title)
     *  TOAL (Original album/movie/show title)
     */
    QString mAlbum;
    
    //! The album media item's track number.
    /**
     * Nepomuk direction:
     *  nid3:trackNumber: http://www.semanticdesktop.org/ontologies/nid3/#trackNumber
     * ID3:
     *  TRCK
     */
    int     mTrackNumber;
  public:
    //! Returns the album media item's album's name.
    QString album();
    
    //! Returns the album media item's track number.
    int     trackNumber();
  public:
    //! Set the album media item's album's name.
    /*!
     * Need be overloaded because the file name is in MediaItem
     * \param album the album's name.
     */
    virtual void setAlbum(QString album) = 0;
    
    //! Set the album media item's track number.
    /*!
     * Need be overloaded because the file name is in MediaItem
     * \param trackNumber the audio's track number.
     */
    virtual void setTrackNumber(int trackNumber) = 0;
  public:
    AlbumMediaItemData(KUrl file);
};

#endif //PLAYBAK_ALBUMMEDIAITEMDATA_H
