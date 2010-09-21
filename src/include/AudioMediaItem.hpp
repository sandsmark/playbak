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

#ifndef PLAYBAK_AUDIOMEDIAITEM_H
#define PLAYBAK_AUDIOMEDIAITEM_H

#include "AlbumMediaItemData.hpp"
#include "ArtisticalMediaItemData.hpp"
#include "MediaItem.hpp"
#include "PlayableMediaItemData.hpp"

#include <QString>

#include <kurl.h>

//! The audio media item's class.
class AudioMediaItem : public PlayableMediaItemData,
                       public MediaItem
{
  public:
    struct Subtype{
      //! The audio media item's subtypes.
      enum AudioMediaItemSubtype{
        NORMAL = 0,   /*!< Normal audio. */
        INSTRUMENTAL, /*!< Instrumental audio. */
        REMIX,        /*!< Remix audio. */
        VOICE         /*!< Voice audio. */
      };
    };
    
    //! The audio media item's contructor.
    /*!
     * \param url the media source url.
     */
    AudioMediaItem(KURL url);
  private:    
    //! The audio media item's subtype.
    Type::AudioMediaItemSubtype mSubtype;
  public:
    //! Returns the audio media item's subtype.
    Subtype::AudioMediaItemSubtype subtype();
  public:
    //! Set the audio media item's subtype.
    /*!
     * \param subtype the audio's subtype.
     */
    void setSubtype(Subtype::AudioMediaItemSubtype subtype);
};

#endif //PLAYBAK_AUDIOMEDIAITEM_H
