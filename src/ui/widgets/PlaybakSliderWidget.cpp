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
#include <QMouseEvent>
#include <QPainter>
#include <QTime>
#include <QTimer>

#include <PlaybakSliderWidget.h>

PlaybaKSliderWidget::PlaybaKSliderWidget(QWidget* parent): QAbstractSlider(parent)
{
    //_mode = mode;
    setOrientation(Qt::Horizontal);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    mValue = 0;
    mOpacity = 0;
    mOver = false;
    mOverLine = false;
    mPressed = false;
    mMouseX = -1;
    mEffects = new QTimer(this);
    connect( mEffects, SIGNAL(timeout()), SLOT(timeout()));
    //  if(mode == 0 && !Settings::audio_setmaxto120())
    //    setMaximum(100);
    //  else if(mode == 0)
    //    setMaximum(120);
    setMouseTracking(true);
    mediaObject = 0x0l;
}

void PlaybaKSliderWidget::setMode(Mode mode)
{
    mMode = mode;
}

PlaybaKSliderWidget::Mode PlaybaKSliderWidget::mode()
{
  return mMode;
}

void PlaybaKSliderWidget::setMediaObject(Phonon::MediaObject* source)
{
  if (source != 0x0l) {
    // Desconectamos la viaja conexión
    if (mediaObject)
      disconnect(mediaObject,SIGNAL(tick(qint64)),this,SLOT(updateTick(qint64)));
    // Apuntamos al nuevo objeto
    mediaObject = source;
    mediaObject->setTickInterval(500);
    // Conectamos la nueva señal
    connect(mediaObject,SIGNAL(tick(qint64)),this,SLOT(updateTick(qint64)));
  }    
}

void PlaybaKSliderWidget::updateTick(qint64 value)
{
  setValue(value);
}

void PlaybaKSliderWidget::paintEvent(QPaintEvent* ev)
{
    //QSlider::paintEvent(ev);
    QPainter p(this);
    if ( mMode == SeekBar)
    {
        QFont cFont = p.font();
        cFont.setPointSize(8);
        p.setFont(cFont);
    }
    QLinearGradient mainG(0, 0, 0, height()-1);
    mainG.setColorAt(0, QColor::fromRgb(250, 250, 250));
    mainG.setColorAt(0.6, QColor::fromRgb(210, 210, 210));
    mainG.setColorAt(0.7, QColor::fromRgb(194, 194, 194));
    mainG.setColorAt(1, QColor::fromRgb(225, 225, 225));
    p.setPen(QPen(Qt::gray, 1));
    p.setBrush(mainG);
    p.drawRoundedRect(0, 0, width()-1, height()-1, 2, 2);
    p.setPen(Qt::white);
    p.drawLine(2, 1, width()-3, 1);

    mVpos = (width()-2)*(value()/(qreal)maximum());

    QLinearGradient valG(0, 0, 0, height()-2);
    valG.setColorAt(0, QColor::fromRgb(195, 220, 255));
    valG.setColorAt(0.6, QColor::fromRgb(160, 190, 225));
    valG.setColorAt(0.7, QColor::fromRgb(125, 150, 190));
    valG.setColorAt(1, QColor::fromRgb(135, 165, 230));
    p.setPen(Qt::transparent);
    p.setBrush(valG);

    if (value() != minimum())
    {
        p.drawRoundedRect(1, 1, mVpos, height()-2, 0, 0);
    }
    if ( mOpacity!=0)
    {
        p.setBrush(Qt::transparent);
        if ( mOverLine)
        {
            if ( mVpos == 0)
            {
                p.setPen(QColor::fromRgbF(0, 0.4, 1, mOpacity*0.5));
                p.drawLine( mVpos+1, 1, mVpos+1, height()-2);
                //p.drawLine(vPos-1, 1, vPos-1, height()-2);
            }
            else if ( mVpos == width()-2)
            {
                p.setBrush(Qt::transparent);
                p.setPen(QColor::fromRgbF(0, 0.4, 1, mOpacity*0.5));
                p.drawLine( mVpos, 1, mVpos, height()-2);
            }
            else
            {
                p.setBrush(Qt::transparent);
                p.setPen(QColor::fromRgbF(0, 0.4, 1, mOpacity));
                p.drawLine( mVpos, 1, mVpos, height()-2);
                p.setPen(QColor::fromRgbF(0, 0.4, 1, mOpacity*0.5));
                p.drawLine( mVpos+1, 1, mVpos+1, height()-2);
                p.drawLine( mVpos-1, 1, mVpos-1, height()-2);
            }
        }
        if ( mMode == VolumeSlider)
        {
            int textWidth = fontMetrics().width(QString::number(value()) + "%");
            int textHeight = fontMetrics().height();

            if (textWidth < width() - mVpos - 2)
            {
                p.setPen(QColor::fromRgbF(0, 0, 0, mOpacity));
                p.drawText( mVpos+2, height()/2+textHeight/2-2, QString::number(value()) + "%");
            }
            else {
                p.setPen(QColor::fromRgbF(1, 1, 1, mOpacity));
                p.drawText( mVpos-1-textWidth, height()/2+textHeight/2-2, QString::number(value()) + "%");
            }
        }
        else
        {
            QTime currentTime((value() / 3600000) % 60, (value() / 60000) % 60, (value() / 1000) % 60);
            QString time(currentTime.toString("mm:ss"));
            int textWidth = QFontMetrics(p.font()).width(time);
            int textHeight = QFontMetrics(p.font()).height();

            QTime mouseTime(( mMouseVal / 3600000) % 60, ( mMouseVal / 60000) % 60, ( mMouseVal / 1000) % 60);
            QString mouseTextTime(mouseTime.toString("mm:ss"));
            int textMouseWidth = QFontMetrics(p.font()).width(mouseTextTime);

            if ( mOverLine)
            {
                if (textWidth < mVpos)
                {
                    p.setPen(QColor::fromRgbF(1, 1, 1, mOpacity));
                    p.drawText( mVpos-1-textWidth, height()/2+textHeight/2-3, time);
                }
                else
                {
                    p.setPen(QColor::fromRgbF(0, 0, 0, mOpacity));
                    p.drawText( mVpos+2, height()/2+textHeight/2-3, time);
                }
            }
            else
            {
                if ( mMouseX + 2 + textMouseWidth < mVpos)
                {
                    p.setPen(QColor::fromRgbF(1, 1, 1, mOpacity));
                    p.drawText( mMouseX + 2, height()/2+textHeight/2-3, mouseTextTime);
                }
                else if ( mMouseX + 2 < mVpos)
                {
                    p.setPen(QColor::fromRgbF(1, 1, 1, mOpacity));
                    p.drawText( mMouseX - textMouseWidth, height()/2+textHeight/2-3, mouseTextTime);
                }
                else if ( mMouseX - 2 - textMouseWidth > mVpos)
                {
                    p.setPen(QColor::fromRgbF(0, 0, 0, mOpacity));
                    p.drawText( mMouseX - textMouseWidth, height()/2+textHeight/2-3, mouseTextTime);
                }
                else
                {
                    p.setPen(QColor::fromRgbF(0, 0, 0, mOpacity));
                    p.drawText( mVpos+2, height()/2+textHeight/2-3, mouseTextTime);
                }
            }
        }
    }
    //p.drawLine(1, 6, width()-2, 6);
}

void PlaybaKSliderWidget::timeout()
{
    if ( mOver) {
        mOpacity += 0.25;
    }
    else {
        mOpacity -= 0.1;
    }
    if ( mOpacity > 1.0) {
        mOpacity = 1;
        mEffects->stop();
    }
    else if ( mOpacity < 0.0) {
        mOpacity = 0;
        mMouseX = -1;
        mEffects->stop();
    }
    update();
}
/*
* void PlaybaKSliderWidget::lineTimeout()
* {
*  if(overLine) { lineOpacity += 0.25; }
*  else { lineOpacity -= 0.1; }
*  if(lineOpacity > 1.0) { lineOpacity = 1; effects->stop(); }
*  else if(lineOpacity < 0.0) { lineOpacity = 0; effects->stop(); }
*  update();
* }*/

void PlaybaKSliderWidget::mouseMoveEvent(QMouseEvent* ev)
{
    //QSlider::mouseMoveEvent(ev);
    //effects->start(40);
    mMouseVal = maximum() * (ev->x()/(qreal)width());
    mMouseX = ev->x();
    if ( mMouseX > width()) {
        mMouseX = width();
    }
    else if ( mMouseX < 0) {
        mMouseX = 0;
    }
    if ( mMouseX - 4 < mVpos && mMouseX + 4 > mVpos)
    {
        mOverLine = true;
    }
    else mOverLine = false;
    if ( mPressed) {
        if ( mMouseVal >= minimum() && mMouseVal <= maximum())
        {
            mValue = mMouseVal;
        }
        else if ( mMouseVal < minimum())
            mValue = minimum();
        else if ( mMouseVal > minimum())
            mValue = maximum();
        //if(Settings::interface_seekwhilemoving())
        setValue(mValue);

        emit valueChanged(mValue);
    }
//     lineFade->start(40);
    update();
}
void PlaybaKSliderWidget::mousePressEvent(QMouseEvent* ev)
{
    //QWidget::mousePressEvent();
    if (ev->button() == Qt::LeftButton) {
        mPressed = true;
        mMouseVal = maximum() * (ev->x()/(qreal)width());
        if ( mMouseVal >= minimum() && mMouseVal <= maximum())
        {
            mValue = mMouseVal;
        }
        else if ( mMouseVal < minimum())
            mValue = minimum();
        else if ( mMouseVal > minimum())
            mValue = maximum();
        setValue(mValue);

        emit valueChanged(mValue);
        update();
    }
}
void PlaybaKSliderWidget::mouseReleaseEvent(QMouseEvent* ev)
{
    //QWidget::mouseReleaseEvent();
    if (ev->button() == Qt::LeftButton) {
        mPressed = false;
        setValue(mValue);
        emit valueChanged( mValue);
    }
}
void PlaybaKSliderWidget::wheelEvent(QWheelEvent* e)
{
    //QAbstractSlider::wheelEvent(e);    int numDegrees = delta / 8;
    if (!mPressed) {
        int change = 1;
        int newValue;
        if (e->delta() < 0)
            change = -1;
        if ( mMode != 0)
            ;
        //newValue = _value + change*Settings::interface_mousewheelseek()*1000;
        else
            newValue = mValue + change*5;
        if (newValue >= minimum() && newValue <= maximum()) {
            mValue = newValue;
        }
        else if (newValue < minimum())
            mValue = minimum();
        else if (newValue > minimum())
            mValue = maximum();
        setValue(mValue);
        emit valueChanged( mValue );
        update();
    }
}

void PlaybaKSliderWidget::leaveEvent(QEvent* )
{
    //QWidget::leaveEvent();
    mOver = false;
    mEffects->start(40);
}

void PlaybaKSliderWidget::enterEvent(QEvent* )
{
    //QWidget::enterEvent();
    mOver = true;
    mEffects->start(40);
}
void PlaybaKSliderWidget::setValue(qint64 v)
{
    if (!mPressed)
    {
        mValue = v;
        update();
        if (QObject::sender() != mediaObject)
          emit valueChanged(int(v));
    }
}
int PlaybaKSliderWidget::value()
{
    return mValue;
}
