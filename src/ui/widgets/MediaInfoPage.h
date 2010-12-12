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

#ifndef MEDIAINFOPAGE_H
#define MEDIAINFOPAGE_H

#include <QLabel>
#include <QWidget>

#include <Nepomuk/KRatingWidget>

class MediaItem;

/**
 * This class provides the first page of the media info frame
 * This page isn't interactive
 */
class MediaInfoPage : public QWidget
{
	Q_OBJECT
public:
    MediaInfoPage(QWidget* parent = 0);
private:
    QLabel *albumName;
    QLabel *artistName;
    QLabel *trackName;
    QLabel *cover;
		KRatingWidget* ratingBar;
protected:
    //virtual void paintEvent(QPaintEvent* ev);
    virtual void enterEvent(QEvent* );
    virtual void leaveEvent(QEvent* );
    //virtual void mouseMoveEvent(QMouseEvent* ev);
    //virtual void mousePressEvent(QMouseEvent* );
    //virtual void mouseReleaseEvent(QMouseEvent* );
    //virtual void wheelEvent(QWheelEvent* e);
public slots:
  void setMediaItem( MediaItem* mediaItem);
	void setRating(int rating) { ratingBar->setRating(rating); }
signals:
	void mouseLeave();
	void mouseOver();
};

#endif
