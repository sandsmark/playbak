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

#ifndef PLAYLISTABSTRACTMEDIAITEM_H
#define PLAYLISTABSTRACTMEDIAITEM_H

#include <QPropertyAnimation>
#include <QVector>
#include <QWidget>

#include <PlaylistItemWidget.h>

class KIcon;

namespace Ui {
    class PlaylistAbstractItem;
}

class PlaylistWidget;

class PlaylistAbstractMediaItem : public PlaylistItemWidget
{
    Q_OBJECT
    friend class PlaylistWidget;
public:
    explicit PlaylistAbstractMediaItem(QWidget *parent = 0);
    virtual ~PlaylistAbstractMediaItem();
public:
    QSize sizeHint();
public slots:
    //! Contract the extra info.
    virtual void contract()  = 0;
    //! Expand the extra info.
    virtual void expand() = 0;
protected slots:
    //! Create the extra info.
    virtual void createExtra() = 0;
    //! Emits the moreinfo(QString) signal.
    virtual void emitMoreInfo() = 0;
    //! Toggle the extra info's expand-contract animation direction.
    virtual void toggleAnimation() = 0;
    //! Toggle the extra button's expand-contract animation direction.
    virtual void toggleButtonAnimation() = 0;
    //! Expand or contract the extra info.
    virtual void expandContract() = 0;
    
    //!
    virtual void play();
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *);
    virtual void resizeEvent ( QResizeEvent *event );
signals:

    //! Is emited when the media info is contracted.
    void contracted();
    //! Is emited when the media info is expanded.
    void expanded();
    //! Is emited when the item is called to play.
    void play(int);
    //! Is emited when the item is resized.
    void resized(int row);
    //! Is emited when the the more info's button is pressed.
    /**
      * NOTE Maybe moreInfo(int). See emitMoreInfo().
      */
    void moreInfo(QString);
protected:
    //! The 'add' and 'remove' icons.
    static QVector<KIcon*>    *mExpandButtonIcon;
    //! Add media icon
    static KIcon add_icon;
    //! Remove media icon
    static KIcon remove_icon;
    //! An iterator for mExpandButtonIcon.
    QVector<KIcon*>::iterator mExpandButtonIconIt;
    //! The extra info's expand animation.
    QPropertyAnimation *mExpandAnimation;
    //! The 'add-remove' expand animation.
    QPropertyAnimation *mExpandButtonAnimation;
    //! Indicates if the extra info zone is animating.
    bool mExpandingContracting;
    //! The extra info height.
    int  mExtraHeight;
private:
    Ui::PlaylistAbstractItem *ui;
};

#endif // PLAYLISTABSTRACTMEDIAITEM_H
