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

#ifndef PLAYBAKSLIDERWIDGET_H
#define PLAYBAKSLIDERWIDGET_H

#include <QtGui/QSlider>

/**
* This class provides a QWidget similar to QSlider.
* It is used as volume slider and seek bar.
*/
class PlaybaKSliderWidget : public QAbstractSlider
{
  Q_OBJECT
  Q_PROPERTY(Mode mode READ mode WRITE setMode)
  Q_ENUMS(Mode)
public:
    struct SliderMode
    {
    };
      enum Mode
      {
        VolumeSlider = 0,
        SeekBar
      };
//public:
    PlaybaKSliderWidget(QWidget* parent = 0);
    virtual int value();
    virtual void setValue(int);
    Mode mode();
    void setMode(Mode mode);
private:
    int mValue;
    Mode mMode;
    qreal mOpacity;
    //int lineOpacity;
    QTimer* mEffects;
    //QTimer* lineFade;
    bool mOver;
    bool mOverLine;
    bool mPressed;
    int mMouseVal;
    int mMouseX;
    int mVpos;
    QPixmap* mBackground;
    QPixmap* mBar;
protected:
    virtual void paintEvent(QPaintEvent* ev);
    virtual void enterEvent(QEvent* );
    virtual void leaveEvent(QEvent* );
    virtual void mouseMoveEvent(QMouseEvent* ev);
    virtual void mousePressEvent(QMouseEvent* );
    virtual void mouseReleaseEvent(QMouseEvent* );
    virtual void wheelEvent(QWheelEvent* e);
private slots:
    void timeout();
};

#endif // PLAYBAKSLIDERWIDGET_H
