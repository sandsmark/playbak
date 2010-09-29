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

#ifndef PLAYBAKANIMATEDSLIDERWIDGET_H
#define PLAYBAKANIMATEDSLIDERWIDGET_H

#include <QtGui/QSlider>
#include <QPropertyAnimation>

/**
 * This class provides an animated QSlider.
 * Calling setValueAnimating(int) will make its value change using an animation
 */
class PlaybaKAnimatedSliderWidget : public QSlider
{
  Q_OBJECT
public:
	PlaybaKAnimatedSliderWidget(QWidget*);
	void setValueAnimating(int);
private:
	QPropertyAnimation* mValueAnimation;
protected:
};

#endif // PLAYBAKANIMATEDSLIDERWIDGET_H
