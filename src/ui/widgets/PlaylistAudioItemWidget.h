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

#ifndef PLAYLISTAUDIOITEMWIDGET_H
#define PLAYLISTAUDIOITEMWIDGET_H

#include <PlaylistAbstractMediaItem.h>

#include <KDE/KUrl>

namespace Ui {
    class PlaylistAudioItemWidget;
}

class AudioMediaItem;

class PlaylistAudioItemWidget : public PlaylistAbstractMediaItem
{
  Q_OBJECT
  friend class MainWindow;
public:
    explicit PlaylistAudioItemWidget(KUrl mediaItem, QWidget* parent = 0);
    explicit PlaylistAudioItemWidget(AudioMediaItem &mediaItem, QWidget* parent = 0);
    ~PlaylistAudioItemWidget();
signals:
  void constructPlaylistAudioItemWidget();
private slots:
  void firstConstructPlaylistAudioItemWidget();
public:
  virtual AudioMediaItem* audioMediaItem(){
    return mMediaItem;
  }
  public slots:
    //! Contract the extra info zone.
    virtual void contract() {}
    //! Expand the extra info zone.
    virtual void expand() {}
    //! Mark as selected the audio media item.
    virtual void select() {}
    //! Mark as unselected the audio media item.
    virtual void unselect() {}
public slots:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
protected slots:
    //! Create the extra info zone.
    /*!
     * For optimization reasons, when the item is created,
     * the info extra zone is not created. It's when the user
     * does click in the 'more's button'.
     */
    void createExtra();
    //! Execute the expand-contract extra info' zone animation.
    virtual void expandContract();
    //! Emit the moreinfo signal.
    virtual void emitMoreInfo();
    //! Emit the removed signal.
    virtual void emitRemoved();
    //! Load the metadata
    void loadMetadata();
    //! Toggle the extra info's animation.
    virtual void toggleAnimation();
    //! Toggle the extra info button's animation direction.
    virtual void toggleButtonAnimation();
protected:
  AudioMediaItem *mMediaItem;
protected:
    bool event(QEvent *e);
    void contextMenuEvent(QContextMenuEvent *e);
    void resizeEvent ( QResizeEvent *event );
private:
    Ui::PlaylistAudioItemWidget *ui;
};

#endif // PLAYLISTAUDIOITEMWIDGET_H
