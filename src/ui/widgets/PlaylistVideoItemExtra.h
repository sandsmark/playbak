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

#ifndef PLAYLISTVIDEOITEMEXTRA_H
#define PLAYLISTVIDEOITEMEXTRA_H

#include <QGraphicsScene>
#include <QWidget>

namespace Ui {
    class PlaylistVideoItemExtra;
}

class PlaylistVideoItemWidget;

class PlaylistVideoItemExtra : public QWidget
{
    Q_OBJECT
    friend class PlaylistVideoItemWidget;
public:
    explicit PlaylistVideoItemExtra(QWidget *parent = 0);
    ~PlaylistVideoItemExtra();
signals:
    //! Emited when you do click over the more info's button.
    void moreInfo();
protected:
    //! The album's thumbnail.
    QGraphicsScene mAlbumImageScene; //NOTE Esto va a tener que ser puntero, porque hay tracks que no tienen cover.
private:
    Ui::PlaylistVideoItemExtra *ui;
};

#endif // PLAYLISTAUDIOITEMEXTRA_H
