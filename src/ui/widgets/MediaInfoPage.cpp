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
#include <QtCore/QVariant>

#include <MediaInfoPage.h>

#include <MediaItem.h>
#include <AudioMediaItem.h>

MediaInfoPage::MediaInfoPage(QWidget* parent): QWidget(parent)
{
  int y = 67;
  int w = 151;
  int h = 16;
  QWidget* mw = new QWidget(this);
  mw->setObjectName(QString::fromUtf8("mediaInfoPage1"));
  mw->setStyleSheet(QString::fromUtf8("#mediaInfoPage1 {\n"
                                        "background-color:\n"
                                        "qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ccc, stop: 1.0 #c2c2c2);\n"
                                        "border: 1px solid rgb(150, 150, 150);\n"
                                        "border-radius: 5px;\n"
                                        "}"));
  mw->setGeometry(QRect(0, 0, 220, 64));

  albumName = new QLabel(mw);
  albumName->setObjectName(QString::fromUtf8("albumName"));
  albumName->setGeometry(QRect(y, 31, w, h));
  QFont font;
  //font.setPointSize(9);
  font.setBold(false);
  font.setWeight(50);
  albumName->setFont(font);
  albumName->setText("Album name");
  albumName->setTextFormat(Qt::RichText);
  
  artistName = new QLabel(mw);
  artistName->setObjectName(QString::fromUtf8("artistName"));
  artistName->setGeometry(QRect(y, 3, w, h));
  artistName->setTextFormat(Qt::RichText);
  
  QFont font1;
  //font1.setPointSize(9);
  font1.setBold(true);
  font1.setWeight(75);
  artistName->setFont(font1);
  artistName->setText("Artist name");

  trackName = new QLabel(mw);
  trackName->setObjectName(QString::fromUtf8("trackName"));
  trackName->setGeometry(QRect(y, 17, w, h));
  trackName->setFont(font1);
  trackName->setText("Track name");
  trackName->setTextFormat(Qt::RichText);
  
  cover = new QLabel(this);
  cover->setObjectName(QString::fromUtf8("cover"));
  cover->setGeometry(QRect(0, 0, 64, 64));
  cover->setStyleSheet(QString::fromUtf8("background-image: url('/usr/share/icons/oxygen/64x64/devices/media-optical-blu-ray.png');"));

  ratingBar = new KRatingWidget(mw);
  ratingBar->setGeometry(QRect(66, 45, 80, 16));

  //setMouseTracking(true);
}

void MediaInfoPage::leaveEvent(QEvent* )
{
  //emit mouseLeave();
}

void MediaInfoPage::enterEvent(QEvent* )
{
  //QWidget::enterEvent();
  emit mouseOver();
}

void MediaInfoPage::setMediaItem ( MediaItem* mediaItem )
{
  if(!mediaItem)
  {
    ratingBar->setRating(0);
    artistName->setText("");
    trackName->setText("");
    albumName->setText("");
    return;
  }
  ratingBar->setRating((int)(mediaItem->rating() * 10.0));
  artistName->setText(QString("<marquee>") + mediaItem->artist() + QString("</marquee>"));
  trackName->setText(QString("<marquee>") + mediaItem->title() + QString("</marquee>"));
  if (mediaItem->mimetype().contains("audio/"))
    if (AudioMediaItem *w = qobject_cast<AudioMediaItem*>(mediaItem))
      albumName->setText(QString("<marquee>") + w->album() + QString("</marquee>"));
}

//void MediaInfoPage::mouseMoveEvent(QMouseEvent* )
//{
//	emit mouseOver();
//}
