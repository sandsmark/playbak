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

#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QStringList>
#include <QWidget>
#include <QUrl>

class MediaItem;
class PlaylistAudioItemWidget;

namespace Ui {
    class PlaylistWidget;
}

class PlaylistWidget : public QWidget
{
    Q_OBJECT
    friend class PlaylistAudioItemWidget;
public:
    explicit PlaylistWidget(QWidget *parent = 0);
    ~PlaylistWidget();
    void addItem(QStringList items);
signals:
    //! Emited when a MediaItem is added.
    void itemAdded(MediaItem*);
    
    //! Emited when the Playlist is resized.
    void resized();
    
    //! Emited when a PlaylistItemWidget may be played.
    void play(int);
protected slots:
    //! Reorganize the media item.
    void reorganize(int);
    void paintEvent(QPaintEvent *);
    //! Move the Playlist's content.
    void moveContent(int offset);
    void wheelEvent(QWheelEvent *);
    //! Remove an item in a specific position.
    void removeItem(int);
    //! Manage the item' selection.
    /*!
     * When a item is selected, this is executed.
     * The parameter is the item's position in the Playlist.
     */
    void selectManager(int);
protected:
    void resizeEvent ( QResizeEvent *event );
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
private:
    //! Indicates if necessary reorganize the Playlist elements.
    /*!
     * This is true when the Playlist's content is graphically altered.
     */
    bool mReorganize;
    
    //! Indicates if the 'Shift' key is pressed.
    /*!
     * This is usefull to the multi-item selection.
     */
    bool mShiftPressed;
    //! The position of the children item that emited the signal reorganize.
    /*!
     * This is this way for optimization reasons.
     */
    int mReorganizeItem;
    //! The Playlist's content height.
    int mContentHeight;
    //! The last value of the scrollbar.
    int mLastScrollbarValue;
private:
    Ui::PlaylistWidget *ui;
};

#endif // PLAYLISTWIDGET_H
