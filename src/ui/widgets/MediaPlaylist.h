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

#ifndef PLAYBAK_MEDIAPLAYLIST_H
#define PLAYBAK_MEDIAPLAYLIST_H

#include <QList>
#include <QWidget>

#include <Phonon/AudioOutput>
#include <Phonon/MediaObject>
#include <Phonon/VideoPlayer>

#include <MediaItem.h>
#include <qlistwidget.h>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <qscrollbar.h>
#include <qscrollarea.h>
#include <qpropertyanimation.h>

//! The media playlist's class.
class MediaPlaylist : public QWidget
{
        Q_OBJECT
public:
  
        struct Mode {
                //! The media playlist plzy modes.
                enum MediaPlaylistMode {
                        NORMAL = 0,   /*!< Normal mode. */
                        SHUFFLE_ALL,   /*!< Shuffle mode. */
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

        //! The video player.
        Phonon::VideoPlayer *mVideoPlayer;

        //! The player's volume.
        int mVolume;

        //! Indicates if the palyer is mute.
        bool mMute;
        
        //! Indicates if the Control key is pressed.
        bool mKeyControlPressed;
        
        //! Indicates if the Shift key is pressed.
        bool mKeyShiftPressed;
        
        QPropertyAnimation *mScrollAnimation;
        
        
private: // GUI        
        //! Here the playlist's items should be rendered.
        QWidget *mCanvas;
        
        //! The playlist's scroll area.
        /*!
         * This is mCanvas' parent.
         */
        QScrollArea *mScrollArea;
        
        QScrollBar *mScrollBar;
        
        QHBoxLayout *mLayout;
        
signals:
        void tick(qint64);
        void totalTime(qint64);
        void trackChanged();
        
        //! Emited when the playlist's visual size changes.
        /*!
         * This should be conected with the Playlist's scroll height.
         */
        /*!
         * \param height The new height.
         */
//         void sizeChanged(qint64);
        
//         void playlistSizeChanged(int height);
public:
        //! Returns a media item from specific position at playlist.
        /*!
         * Sinonymous: MediaItem* mediaItem(const int position);
         */
        /*!
         * \param position the position at playlist.
         */
        virtual MediaItem* operator[] ( const int position );

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
        virtual MediaItem* mediaItem ( const int position );

        /*!
         *
         */
        virtual Phonon::MediaObject* mediaObject();

        //! Return the playlist play mode.
        virtual Mode::MediaPlaylistMode mode();

        //! Return the media's total time.
        qint64 currentTotalTime();
public slots:
//         virtual void toggleFullScreen(QMouseEvent *e);
  
        virtual void clearPlaylist();
  
        virtual void updatePositionsFrom(int position);
        
        virtual void sincronizeWithScroll(int value);

        //! Add media items to playlist.
        /*!
        * \param mediaItem the media to add.
        */
        virtual void addItems(QList<MediaItem*> *items);
        
        
        
        virtual void removeItem(int position);
        
        //! Remove the selected items from the playlist.
        virtual void removeSelecteds();

        //! Play the track at specific position.
        /*!
         * \param position the media position.
         */
        virtual void play ( int position );

        //! Set the current media's tick.
        /*!
         * \param tick the media's tick.
         */
        virtual void setTick( int tick);
  
        //! Insert a media playlist at specific position in playlist.
        /*!
         * If position < 0 then insert at end.
         */
        /*!
         * \param position the media's position to add.
         * \param mediaItem the media to add.
         */
        virtual void insert ( int position, MediaItem* mediaItem );

        //! Move a media item from it's position to another position in playlist.
        /*!
         * \param from move from position.
         * \param to move to position.
         */
        virtual void move ( int from, int to );

        //! Remove a media item from playlist.
        /*!
         * \param position the media to remove.
         */
        virtual void remove ( MediaItem* mediaItem );

        //! Remove a media item from playlist.
        /*!
         * \param position the media's position.
         */
        virtual void remove ( const int position );

        virtual void setVolume(qreal volume);

        //! Play current media item.
        virtual void play();

        //! Play next media item.
        virtual void playNext();

        //! Play previous media item.
        virtual void playPrevious();

        //! Pause current media item.
        virtual void pause();

        //! Play or pause the current media item.
        virtual void playPause();

        //! When a MediaItem is selected this method manage the selected items status.
        /*!
         * \param position The MediaItem's position in the playlist.
         */
        virtual void select( const int position );

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
        //! Return the player's mute state.
        /*!
         * Returns true if player is mute.
         */
        virtual bool isMute();
        
        //! Set the current media item.
        /*!
         * This only select a media item, no play it. This is, only set the
         * mCurrent value.
         */
        /*!
         * \param current the current media's position.
         */
        virtual void setCurrent ( const int current );

        //! Set the current media item.
        /*!
         * This only select a media item, no play it. This is, only set the
         * mCurrent value.
         */
        /*!
         * \param media the media to set as current.
         */
        virtual void setCurrent ( MediaItem* media ); //NOTE Not used.

        //! Set the playlist play mode.
        /*!
         * \param mode the playlist play mode.
         */
        virtual void setMode ( const Mode::MediaPlaylistMode mode );

        //! Set the palyer mute state.
        /*!
         * \param mute the mute state.
         */
        virtual void setMute ( const bool mute = true );

        //! Set the output widget.
        /*!
         * \param outputWidget the output widget.
         */
        virtual void setOutputWidget ( QWidget *outputWidget );

        //! Return the player's state.
        virtual Phonon::State state();

        //! Return the player volume.
        virtual int volume();
private:
        void resizeEvent(QResizeEvent *);
        void keyPressEvent(QKeyEvent *e);
        void keyReleaseEvent(QKeyEvent *e);
        void wheelEvent ( QWheelEvent * e );
        int virtualHeight();
public:
        //! The media playlist's constructor.
        MediaPlaylist(QWidget* parent = 0x0L);

        //! The media playlist's destructor.
        virtual ~MediaPlaylist();
};

#endif //PLAYBAK_MEDIAPLAYLIST_H

