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
#include <QFontMetrics>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>
#include <QTimeLine>

#include <PlaybaKGlowTextButton.h>

PlaybaKGlowTextButton::PlaybaKGlowTextButton(QWidget* parent): QGraphicsView(parent)
{
  setFrameStyle(0);
  setStyleSheet("background-color: transparent");
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setAlignment(Qt::AlignLeft | Qt::AlignTop);
  //setAlignment(Qt::AlignCenter);
  setSceneRect(geometry());
  timeLine = new QTimeLine(400, this);
  timeLine->setFrameRange(0, 1000);
  connect(timeLine, SIGNAL(frameChanged(int)), SLOT(changeBluredText()));
  normalText = new PlaybaKGlowTextButtonText("", this);
  bluredText = new PlaybaKGlowTextButtonText("", this);
  bluredText->setOpacity(0);
  bluredText2 = new PlaybaKGlowTextButtonText("", this);
  bluredText2->setOpacity(0);
  QGraphicsScene* scene = new QGraphicsScene(this);
  scene->addItem(bluredText);
  scene->addItem(bluredText2);
  scene->addItem(normalText);
  setScene(scene);
  QGraphicsBlurEffect* mBlur = new QGraphicsBlurEffect(this);
  mBlur->setBlurRadius(3);
  QGraphicsBlurEffect* mBlur2 = new QGraphicsBlurEffect(this);
  mBlur2->setBlurRadius(2);
  bluredText->setGraphicsEffect(mBlur);
  bluredText2->setGraphicsEffect(mBlur2);
}

void PlaybaKGlowTextButton::changeBluredText()
{
  //normalText->readyToUseButtonSize = true;
  //bluredText->readyToUseButtonSize = true;
  //bluredText2->readyToUseButtonSize = true;
  qreal frame = (qreal)timeLine->currentFrame()/1000.;
  bluredText->setOpacity(frame);
  bluredText2->setOpacity(frame);
}

/*void PlaybaKGlowTextButton::paintEvent(QPaintEvent* ev)
{
  QPainter p(this);
  qreal frame = (qreal)timeLine->currentFrame()/1000.;
  //p.setOpacity(frame);
  //p.drawPixmap(0, 0, width(), height(), QPixmap("/home/gil/glow.png"));
  p.setFont(font());
  QFontMetrics fontMetrics = QFontMetrics(p.font());
  int x = width()/2-fontMetrics.width(text())/2;
  int y = fontMetrics.height();
  p.setOpacity(frame/2);
  p.drawText(x, y, text());
  KPushButton::paintEvent(ev);
  /* /*p.drawText(x-1, y, text());
  p.drawText(x, y-1, text());
  p.drawText(x+1, y, text());
  p.drawText(x, y+1, text());

  p.drawText(x-1, y-1, text());
  p.drawText(x+1, y-1, text());
  p.drawText(x+1, y-1, text());
  p.drawText(x+1, y+1, text());
  p.drawText(x-2, y, text());
  p.drawText(x, y-2, text());
  p.drawText(x+2, y, text());
  p.drawText(x, y+2, text());* /
  p.setOpacity(1);
  p.drawText(x, y, text());
  //p.drawPixmap(0, 0, width(), height(), QPixmap(mOverIcon));
  //p.drawPixmap(0, 0, width(), height(), QPixmap("/home/gil/glow.png"));
  //KIcon(mOverIcon).pixmap(iconSize().width(), iconSize().height()
  //p.drawLine(0, 0, 20, 20);
}*/

void PlaybaKGlowTextButton::leaveEvent(QEvent* )
{
  //QWidget::leaveEvent();
  timeLine->stop();
  timeLine->setDirection(QTimeLine::Backward);
  timeLine->start();
}

void PlaybaKGlowTextButton::enterEvent(QEvent* )
{
  //QWidget::enterEvent();
  timeLine->stop();
  timeLine->setDirection(QTimeLine::Forward);
  timeLine->start();
}