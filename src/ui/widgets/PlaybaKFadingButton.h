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

#ifndef PLAYBAKFADINGBUTTON_H
#define PLAYBAKFADINGBUTTON_H

#include <KPushButton>
#include <QTimeLine>

/**
 * This class provides a fading KPushButton
 */
class PlaybaKFadingButton : public KPushButton
{
  Q_OBJECT
  Q_PROPERTY(QString overIcon READ overIcon WRITE setOverIcon)
public:
	PlaybaKFadingButton(QWidget* parent = 0);
	QString overIcon();
	void setOverIcon(QString);
	//void setOverIcon(QIcon);
private:
	QTimeLine *timeLine;
	QString mOverIcon;
protected:
	virtual void paintEvent(QPaintEvent*);
  virtual void enterEvent(QEvent* );
  virtual void leaveEvent(QEvent* );
};

#endif // PLAYBAKSLIDERWIDGET_H
