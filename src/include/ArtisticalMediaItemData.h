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

#ifndef PLAYBAK_ARTISTICALMEDIAITEMDATA_H
#define PLAYBAK_ARTISTICALMEDIAITEMDATA_H

#include <QString>

class ArtisticalMediaItemData
{
  private:
    //! The artistical media item's artist's website.
    /**
     * Nepomuk direction:
     *  nid3:officialArtistWebsite: http://www.semanticdesktop.org/ontologies/nid3/#officialArtistWebpage
     * ID3:
     *   WOAR (Official artist/performer webpage)
     */
    KURL    mArtistWebsite;
    
    //! The artistical media item's orginal version.
    /**
     * Nepomuk has not.
     * ID3 has not.
     */
    QString     mOriginalMedia;
  public:
    //! Returns the artistical media item's website.
    KURL    artistWebsite();
    
    //! Return the artistical media item's original version.
    QString     originalMedia();
  public:
    //! Set the artistical media item's website.
    /*!
     * \param url the artist's website url.
     */
    void setArtistWebsite(KURL url);
    
    //! Set the artistical media item's original version.
    void setOriginalMedia(int linkId);
}

#endif //PLAYBAK_ARTISTICALMEDIAITEMDATA_H
 
