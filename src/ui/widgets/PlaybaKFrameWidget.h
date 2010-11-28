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

#ifndef PLAYBAKFRAMEWIDGET_H
#define PLAYBAKFRAMEWIDGET_H

#include <QPaintEngine>
#include <QWidget>

class PlaybaKFrameWidget : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(qreal topColor READ topColor WRITE setTopColor)
  Q_PROPERTY(qreal bottomColor READ bottomColor WRITE setBottomColor)
  Q_PROPERTY(qreal borderColor READ borderColor WRITE setBorderColor)
  Q_PROPERTY(qreal radius READ radius WRITE setRadius)
public:
    /**
    * Default Constructor
    */
    PlaybaKFrameWidget(QWidget *parent);

    /**
    * Default Destructor
    */
    virtual ~PlaybaKFrameWidget();

    struct FrameTypes {
      enum Type {
        Normal = 0,
        BlackBottom,
        GrayBottom
      };
    };
    void setTopColor(qreal);
    void setBottomColor(qreal);
    void setBorderColor(qreal);
    void setOpacity(qreal);
    void setRadius(qreal);
    void setType(int);
    qreal topColor();
    qreal bottomColor();
    qreal borderColor();
    qreal opacity();
    qreal radius();
    int type();
protected:
    virtual void paintEvent(QPaintEvent* );
    qreal mTopColor;
    qreal mBottomColor;
    qreal mBorderColor;
    qreal mOpacity;
    qreal mRadius;
    int mType;
};

#endif // PLAYBAKFRAMEWIDGET_H
