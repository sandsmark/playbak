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

#ifndef PLAYBAK_MEDIACONTROLS_H
#define PLAYBAK_MEDIACONTROLS_H

//! The media control's class.
class MediaControls {
  private:
    //! The global volume.
    int mVolume;
  public:
    //! Play the next media item from playlist.
    void next();
    
    //! Play the current media item from playlist.
    void play();
    
    //! Play the next previous item from playlist.
    void previous();
  public:  
    //! Returns the global volume.
    int  volume();
  public:
    //! Increses the golbal volume.
    /*!
     * \param increment the volume increment value.
     */
    void volumeUp(const int increment);
    
    //! Decreases the global volume.
    /*!
     * \param decrement the volume decrement value.
     */
    void volumeDown(const int decrement);
  public:
    //! Set the global volume.
    /*!
     * \param volume the volume value.
     */
    void setVolume(const int volume);
};

#endif //PLAYBAK_MEDIACONTROLS_H
