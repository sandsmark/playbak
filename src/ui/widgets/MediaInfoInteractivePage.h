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

#ifndef MEDIAINFOINTERACTIVEPAGE_H
#define MEDIAINFOINTERACTIVEPAGE_H

#include <QWidget>
#include <QLabel>
//#include <QHBoxLayout>
#include <QSpacerItem>
#include <QPushButton>
#include <QFormLayout>
#include <Nepomuk/KRatingWidget>

/**
 * This class provides the first page of the media info frame
 * This page is interactive
 */
class MediaInfoInteractivePage : public QWidget
{
	Q_OBJECT
public:
	MediaInfoInteractivePage(QWidget* parent = 0);
private:
	QWidget *widget_2;
	QFormLayout *formLayout;
	QLabel *mInfoValue1;
	QLabel *mInfoValue2;
	QLabel *mInfoValue3;
	QLabel *mInfo1;
	QLabel *mInfo2;
	QLabel *mInfo3;
	QPushButton *infoFrameSettings;
	KRatingWidget* ratingBar;
	void retranslateUi();
protected:
    //virtual void paintEvent(QPaintEvent* ev);
    virtual void leaveEvent(QEvent* );
    //virtual void leaveEvent(QEvent* );
    //virtual void mouseMoveEvent(QMouseEvent* ev);
    //virtual void mousePressEvent(QMouseEvent* );
    //virtual void mouseReleaseEvent(QMouseEvent* );
    //virtual void wheelEvent(QWheelEvent* e);
signals:
	void mouseLeave();
	/**
	 * Use only to update KRatingBar's rating on the other page
	 */
	void ratingChanged(int);
};

#endif
