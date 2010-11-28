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

#include <QEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QTimeLine>

#include <PlaybaKFadingButton.h>

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