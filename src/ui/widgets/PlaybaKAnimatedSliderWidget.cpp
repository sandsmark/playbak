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

#include <QtGui/QSlider>
#include "PlaybaKAnimatedSliderWidget.h"

PlaybaKAnimatedSliderWidget::PlaybaKAnimatedSliderWidget(QWidget* parent=0) : QSlider(parent)
{
	mValueAnimation = new QPropertyAnimation(this, "value");
	mValueAnimation->setDuration(500);
	//TODO choose an easing curve to make the animation look better (these 2 are my favorites)
	//mValueAnimation->setEasingCurve(QEasingCurve::OutBack);
	mValueAnimation->setEasingCurve(QEasingCurve::InOutQuint);
}

void PlaybaKAnimatedSliderWidget::setValueAnimating(int _value)
{
	//TODO don't animate if it isn't visible to save CPU and lower media loading time
	//TODO don't emit the valueChanged signal while it is being animated (I'm not sure if this happens or not)
	mValueAnimation->setEndValue(_value);
	mValueAnimation->start();
}
