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

#ifndef PLAYLISTITEMWIDGET_H
#define PLAYLISTITEMWIDGET_H

#include <QGraphicsScene>
#include <QWidget>

#include <MediaItem.h>

class MediaPlaylist;
class PlaylistAudioItemWidget;
class PlaylistVideoItemWidget;

class PlaylistItemWidget : public QWidget
{
    Q_OBJECT
    friend class MediaPlaylist;
    friend class PlaylistAudioItemWidget;
    friend class PlaylistVideoItemWidget;
public:
    Q_PROPERTY(bool selected READ getSelected WRITE setSelected)
public: // Q_PROPERTY
    bool getSelected(){return mSelected;}
    void setSelected(bool value){mSelected = value;}
    
    explicit PlaylistItemWidget(QWidget *parent = 0);
    ~PlaylistItemWidget();
public slots:
    //! Mark this media item as selected.
    virtual void select() = 0;
    
    //! Mark this media item as unselected.
    virtual void unselect() = 0;
protected slots:
    //! Emits the removed(int) signal.
    virtual void emitRemoved() = 0;
signals:
    //! Is emited when the item is clicked.
    /*!
     * The parameter is the position in the playlist.
     */
    void selected(int);
    
    //! Is emited the item is unselected.
    void unselected();
    
    //! Is emited when the item may be removed from the playlist.
    /*!
     * Note the item is not self removed from the playlist.
     * The parameter is the position in the playlist.
     */
    void removed(int);
    
    //! Is emited when the item is added.
    /*!
     * NOTE: not implemented yet and is not usefull.
     */
    void added();

protected:
    //! The last height value.
    /*!
     * This value is necessary to the Playlist's scrollbar.
     */
    int  mLastHeight;
    
    //! Indicates if the media item is selected.
    bool mSelected;
    
    //! The position in the Playlist parent.
    /*!
     * When a media item is added to a Playlist, the Playlist set this value.
     * The default value is -1.
     */
    int  mParentChildPos;
    
    //! The media item.
    MediaItem *mMediaItem;
};

#endif // PLAYLISTITEMWIDGET_H
 
