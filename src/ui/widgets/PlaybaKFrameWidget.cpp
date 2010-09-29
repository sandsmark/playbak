/*
    Copyright 2010 Gil Castro
    KDE Media Player is distributed under the terms of the GNU General Public License
    
    This file is part of KDE Media Player.

    KDE Media Player is free software: you can redistribute it and/or modify  it
    under the terms of the GNU General Public License as published by the Free
    Software Foundation, either version 3 of the License, or (at your option) any
    later version.

    KDE Media Player is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
    A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License  along with KDE
    Media Player.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "PlaybaKFrameWidget.h"
#include "settings.h"
#include <qpaintengine.h>
#include <QPaintEvent>
#include <QApplication>

//TODO make it use theme settings (I commented the lines that used the color chosen by the user)
/**
 * This class provides a framed QWidget
 */
PlaybaKFrameWidget::PlaybaKFrameWidget(QWidget* parent): QWidget(parent)
{
  mType = 1;
  mTopColor = 0.70;
  mBottomColor = 0.80;
  mBorderColor = 0.50;
  mOpacity = 1;
  mRadius = 5;
}

void PlaybaKFrameWidget::paintEvent(QPaintEvent* )
{
    QPainter RectanglePainter(this);    
    RectanglePainter.setRenderHint(QPainter::Antialiasing);
    if(mType != 3)
    {
      if(mType == 1){ RectanglePainter.fillRect(0, height()-4, width(), 4, Qt::black); }
      else if(mType == 2){ RectanglePainter.fillRect(0, height()-4, width(), 4, QColor::fromRgbF(0.90, 0.90, 0.90, 1)); }
      QLinearGradient GradBack(0,0,0,height());
      //GradBack.setColorAt(0, QColor::fromRgbF(1-(1-mTopColor)*Settings::appearance_maincolor_r() , 1-(1-mTopColor)*Settings::appearance_maincolor_g(), 1-(1-mTopColor)*Settings::appearance_maincolor_b(), mOpacity)); //190
			GradBack.setColorAt(0, QColor::fromRgbF(1-(1-mTopColor), 1-(1-mTopColor), 1-(1-mTopColor), mOpacity));
      //GradBack.setColorAt(1, QColor::fromRgbF(1-(1-mBottomColor)*Settings::appearance_maincolor_r(), 1-(1-mBottomColor)*Settings::appearance_maincolor_g(), 1-(1-mBottomColor)*Settings::appearance_maincolor_b(), mOpacity)); //215
			GradBack.setColorAt(1, QColor::fromRgbF(1-(1-mBottomColor), 1-(1-mBottomColor), 1-(1-mBottomColor), mOpacity));
      QBrush RectangleBackground(GradBack);
      //RectanglePainter.setPen(QPen(QColor::fromRgbF(1-(1-mBorderColor)*Settings::appearance_maincolor_r(), 1-(1-mBorderColor)*Settings::appearance_maincolor_g(), 1-(1-mBorderColor)*Settings::appearance_maincolor_b(), mOpacity), 1));
			RectanglePainter.setPen(QPen(QColor::fromRgbF(1-(1-mBorderColor), 1-(1-mBorderColor), 1-(1-mBorderColor), mOpacity), 1));
      RectanglePainter.setBrush(RectangleBackground);
      RectanglePainter.drawRoundedRect(0, 0, width(), height(), mRadius, mRadius);
    }
    else
    {
      QLinearGradient GradBack(0,0,0,height());
//      GradBack.setColorAt(0, QColor::fromRgbF(1-(1-mTopColor)*Settings::appearance_maincolor_r(), 1-(1-mTopColor)*Settings::appearance_maincolor_g(), 1-(1-mTopColor)*Settings::appearance_maincolor_b(), mOpacity)); //190
			GradBack.setColorAt(0, QColor::fromRgbF(1-(1-mTopColor), 1-(1-mTopColor), 1-(1-mTopColor), mOpacity));
      //GradBack.setColorAt(1, QColor::fromRgbF(1-(1-mBottomColor)*Settings::appearance_maincolor_r(), 1-(1-mBottomColor)*Settings::appearance_maincolor_g(), 1-(1-mBottomColor)*Settings::appearance_maincolor_b(), mOpacity)); //215
			GradBack.setColorAt(1, QColor::fromRgbF(1-(1-mBottomColor), 1-(1-mBottomColor), 1-(1-mBottomColor), mOpacity));
      QBrush RectangleBackground(GradBack);
      //RectanglePainter.setPen(QPen(QColor::fromRgbF(1-(1-mBorderColor)*Settings::appearance_maincolor_r(), 1-(1-mBorderColor)*Settings::appearance_maincolor_g(), 1-(1-mBorderColor)*Settings::appearance_maincolor_b(), mOpacity), 1));
			RectanglePainter.setPen(QPen(QColor::fromRgbF(1-(1-mBorderColor), 1-(1-mBorderColor), 1-(1-mBorderColor), mOpacity), 1));
      RectanglePainter.setBrush(RectangleBackground);
      RectanglePainter.drawRoundedRect(2, 2, width()-4, height()-4, mRadius, mRadius);
    }
}

qreal PlaybaKFrameWidget::bottomColor()
{ return mBottomColor; }
qreal PlaybaKFrameWidget::topColor()
{ return mTopColor; }
qreal PlaybaKFrameWidget::borderColor()
{ return mBorderColor; }
qreal PlaybaKFrameWidget::opacity()
{ return mOpacity; }
qreal PlaybaKFrameWidget::radius()
{ return mRadius; }
int PlaybaKFrameWidget::type()
{ return mType; }

void PlaybaKFrameWidget::setBottomColor(qreal color)
{ mBottomColor = color; update();}
void PlaybaKFrameWidget::setTopColor(qreal color)
{ mTopColor = color; update();}
void PlaybaKFrameWidget::setBorderColor(qreal color)
{ mBorderColor = color; update();}
void PlaybaKFrameWidget::setOpacity(qreal value)
{ mOpacity = value; update();}
void PlaybaKFrameWidget::setRadius(qreal value)
{ mRadius = value; update();}
//0 = normal; 1 = black bottom; 2 = gray bottom; 3 = with margin
void PlaybaKFrameWidget::setType(int value)
{ mType = value; update(); }

PlaybaKFrameWidget::~PlaybaKFrameWidget()
{

}

