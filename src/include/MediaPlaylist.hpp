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

#ifndef PLAYBAK_MEDIAPLAYLIST_H 
#define PLAYBAK_MEDIAPLAYLIST_H

#include "MediaItem.hpp"

#include <QList>
#include <QWidget>
#include <phonon/AudioOutput>
#include <phonon/MediaObject>
#include <phonon/VideoPlayer>

//! The media playlist's class.
class MediaPlaylist {
  public:
    struct Mode {
      //! The media playlist plzy modes.
      enum MediaPlaylistMode {
        NORMAL = 0,   /*!< Normal mode. */
        RANDOM_ALL,   /*!< Random all mode. */
        LOOP_MEDIA,   /*!< Repeat one media mode. */
        LOOP_PLAYLIST /*!< Repeat playlist mode. */
      };
    };
  private:
    //! The media playlist play mode.
    Mode::MediaPlaylistMode mMode;
    
    //! The current media item.
    int mCurrent;
    
    //!  The playlist's media items.
    QList<MediaItem*> mItemList;

    //! The output widget.
    QWidget *mOutputWidget;

    Phonon::VideoPlayer *mVideoPlayer;
  public:
    //! Returns an media item from specific position at playlist.
    /*!
     * Sinonymous: MediaItem* mediaItem(const int position);
     */
    /*!
     * \param position the position at playlist.
     */
    virtual MediaItem* operator[](const int position);
    
    //! Add an media item to playlist.
    /*!
     * \param mediaItem the media to add.
     */
    virtual void addMediaItem(MediaItem* mediaItem);
    
    //! Count media items in playlist.
    virtual int count();

    //! Return the current media item position.
    virtual int current();
    
    //! Return the current media item.
    /*!
     * If playlist is empty then return 0x0L.
     */
    virtual MediaItem* mediaItem();
    
    //! Return a media item at specific position in playlist.
    /*!
     * \param position the media's position.
     */
    virtual MediaItem* mediaItem(const int position);
    
    //! Retur the playlist play mode.
    virtual Mode::MediaPlaylistMode mode();
  public:
    //! Insert a media playlist at specific position in playlist.
    /*!
     * If position < 0 then insert at end.
     */
    /*!
     * \param position the media's position to add.
     * \param mediaItem the media to add.
     */
    virtual void insert(int position, MediaItem* mediaItem);
    
    //! Move a media item from it's position to another position in playlist.
    /*!
     * \param from move from position.
     * \param to move to position.
     */
    virtual void move(int from, int to);
    
    //! Remove a media item from playlist.
    /*!
     * \param position the media to remove.
     */
    virtual void remove(MediaItem* mediaItem);
    
    //! Remove a media item from playlist.
    /*!
     * \param position the media's position.
     */
    virtual void remove(const int position);

    //! Play current media item.
    virtual void play();

    //! Pause current media item.
    virtual void pause();

    //! Play or pause the current media item.
    virtual void playPause();
    
    //! Select a media item at specific position in playlist.
    /*!
     * This only select a media item, no play it. This is, only set the
     * mCurrent value.
     */
    /*!
     * \param position the media's position.
     */
    virtual void select(const int position);
    
    //! Select the next media item at playlist.
    /*!
     * This only select a media item, no play it. This is, only set the
     * mCurrent value.
     */
    virtual void selectNext();
    
    //! Select the previous media item at playlist.
    /*!
     * This only select a media item, no play it. This is, only set the
     * mCurrent value.
     */
    virtual void selectPrevious();
  public:
    //! Set the current media item.
    /*!
     * This only select a media item, no play it. This is, only set the
     * mCurrent value.
     */
    /*!
     * \param current the current media's position.
     */
    virtual void setCurrent(const int current);
    
    //! Set the current media item.
    /*!
     * This only select a media item, no play it. This is, only set the
     * mCurrent value.
     */
    /*!
     * \param media the media to set as current.
     */
    virtual void setCurrent(MediaItem* media);
    
    //! Set the playlist play mode.
    /*!
     * \param mode the playlist play mode.
     */
    virtual void setMode(const Mode::MediaPlaylistMode mode);

    //! Set the output widget.
    /*!
     * \param outputWidget the output widget.
     */
    virtual void setOutputWidget(QWidget *outputWidget);
  public:
    //! The media playlist's destructor.
    virtual ~MediaPlaylist();
};

#endif //PLAYBAK_MEDIAPLAYLIST_H

