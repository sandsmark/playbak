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

#ifndef PLAYBAKFRAMEWIDGET_H
#define PLAYBAKFRAMEWIDGET_H

#include <QWidget>
#include <qpaintengine.h>

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
