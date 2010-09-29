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

#ifndef PLAYBAKGLOWTEXTBUTTON_H
#define PLAYBAKGLOWTEXTBUTTON_H

#include <KPushButton>
#include <QTimeLine>
#include <QGraphicsView>
#include <QGraphicsBlurEffect>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsItem>
#include <QGraphicsWidget>
#include <QFontMetrics>
#include <QResizeEvent>

class PlaybaKGlowTextButtonText : public QGraphicsItem
{
public:
	PlaybaKGlowTextButtonText(QString text, QWidget* widget, QGraphicsItem * parent = 0 ) : QGraphicsItem(parent)
	{ mWidget = widget; mText = text; }
	void setText(QString text) { mText = text; }
	QString text() { return mText; }
	//bool readyToUseButtonSize;
	//QRect boundingRect;
private:
	QWidget* mWidget;
	QString mText;
public:
	QRectF boundingRect() const
	{
		//if(!readyToUseButtonSize)
		//	return QRect(0, 0, 0, 0);
		//else
			return QRect(0, 0, mWidget->geometry().width(), mWidget->geometry().height());
	}
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0)
	{
		painter->setPen(Qt::white);
		//painter->setBrush(Qt::white);
		//painter->drawText(0, -10, "kjhgf");
		QFontMetrics m(painter->font());
		//painter->drawText(-4, 15, QString::number(mWidget->geometry().width()));
		painter->drawText(mWidget->geometry().width()/2 - m.width(mText)/2 + 3, m.height()/2 + mWidget->geometry().height()/2 + 1, mText);
		//painter->setBrush(QColor(255, 255, 255, 50));
		//painter->drawRect(0, 0, mWidget->geometry().width(), mWidget->geometry().height());
	}
};

/**
 * This class provides 
 */
class PlaybaKGlowTextButton : public QGraphicsView
{
  Q_OBJECT
  Q_PROPERTY(QString text READ text WRITE setText)
public:
	PlaybaKGlowTextButton(QWidget* parent = 0);
	QString text() { return ""; } //normalText->text(); }
	void setText(QString text) { normalText->setText(text); bluredText->setText(text); bluredText2->setText(text); }
private:
	//QGraphicsBlurEffect* mBlur;
	QTimeLine *timeLine;
	PlaybaKGlowTextButtonText* normalText;
	PlaybaKGlowTextButtonText* bluredText;
	PlaybaKGlowTextButtonText* bluredText2;
protected:
	//virtual void paintEvent(QPaintEvent*);
	virtual void resizeEvent(QResizeEvent* event)
	{
		QWidget::resizeEvent(event);
		QFontMetrics m(font()); setMinimumSize(m.width(normalText->text()) + 4, 22);
	}
  virtual void enterEvent(QEvent* );
  virtual void leaveEvent(QEvent* );
	virtual void wheelEvent (QWheelEvent * ) {}
private slots:
	void changeBluredText();
};

#endif
