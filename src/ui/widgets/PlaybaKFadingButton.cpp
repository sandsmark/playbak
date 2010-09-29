/*
 *    Copyright 2010 Gil Castro
 *    KDE Media Player is distributed under the terms of the GNU General Public License
 *
 *    This file is part of KDE Media Player.
 *
 *    KDE Media Player is free software: you can redistribute it and/or modify  it
 *    under the terms of the GNU General Public License as published by the Free
 *    Software Foundation, either version 3 of the License, or (at your option) any
 *    later version.
 *
 *    KDE Media Player is distributed in the hope that it will be useful, but WITHOUT
 *    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 *    A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License  along with KDE
 *    Media Player.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "PlaybaKFadingButton.h"

#include <qevent.h>
#include <QPaintEvent>
#include <QPainter>
#include <QTimeLine>

PlaybaKFadingButton::PlaybaKFadingButton(QWidget* parent): KPushButton(parent)
{
	timeLine = new QTimeLine(200, this);
	timeLine->setFrameRange(0, 1000);
	connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(update()));
}

void PlaybaKFadingButton::paintEvent(QPaintEvent* ev)
{
	//KPushButton::paintEvent(ev);
	QPainter p(this);
	qreal frame = (qreal)timeLine->currentFrame()/1000.;
	//p.setOpacity(frame);
	//p.drawPixmap(0, 0, width(), height(), QPixmap("/home/gil/glow.png"));
	
	p.setOpacity(1);
	icon().paint(&p, width()/2 - iconSize().width()/2, height()/2 - iconSize().height()/2, iconSize().width(), iconSize().height());
	//KIcon(mOverIcon).pixmap(iconSize().width(), iconSize().height()
	
	p.setOpacity(frame);
	//p.drawPixmap(0, 0, width(), height(), QPixmap(mOverIcon));
	p.drawPixmap(0, 0, width(), height(), QPixmap("/home/gil/Projectos/play.png"));
	//p.drawLine(0, 0, 20, 20);
}

void PlaybaKFadingButton::leaveEvent(QEvent* )
{
	//QWidget::leaveEvent();
	timeLine->setDirection(QTimeLine::Backward);
  timeLine->start();
}

void PlaybaKFadingButton::enterEvent(QEvent* )
{
	//QWidget::enterEvent();
	timeLine->setDirection(QTimeLine::Forward);
    timeLine->start();
}

QString PlaybaKFadingButton::overIcon()
{
	return mOverIcon;
}

void PlaybaKFadingButton::setOverIcon(QString overIcon)
{
	mOverIcon = overIcon;
}