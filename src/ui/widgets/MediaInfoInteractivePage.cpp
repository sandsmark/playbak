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

#include <KDE/KIcon>
#include <KDE/KLocale>

#include <MediaInfoInteractivePage.h>

#include <MediaItem.h>
#include <AudioMediaItem.h>

MediaInfoInteractivePage::MediaInfoInteractivePage(QWidget* parent): QWidget(parent)
{
  //int y = 67;
  //int w = 151;
  //int h = 16;
  QWidget* mw = new QWidget(this);
  mw->setObjectName(QString::fromUtf8("page"));
  mw->setStyleSheet(QString::fromUtf8("#page {\n"
                                      "background-color:\n"
                                      "qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ccc, stop: 1.0 #c2c2c2);\n"
                                      "border: 1px solid rgb(150, 150, 150);\n"
                                      "border-radius: 5px;\n"
                                      "}"));
  mw->setGeometry(QRect(0, 0, 220, 64));

  widget_2 = new QWidget(mw);
  widget_2->setObjectName(QString::fromUtf8("widget_2"));
  widget_2->setGeometry(QRect(4, 2, 212, 42));

  formLayout = new QFormLayout(widget_2);
  formLayout->setSpacing(6);
  formLayout->setContentsMargins(0, 0, 0, 0);
  formLayout->setObjectName(QString::fromUtf8("formLayout"));
  formLayout->setVerticalSpacing(0);
  mInfoValue1 = new QLabel(widget_2);

  mInfoValue1->setObjectName(QString::fromUtf8("mInfoValue1"));
  QFont font;
  font.setPointSize(8);
  mInfoValue1->setFont(font);
  formLayout->setWidget(1, QFormLayout::FieldRole, mInfoValue1);

  mInfoValue2 = new QLabel(widget_2);
  mInfoValue2->setObjectName(QString::fromUtf8("mInfoValue2"));
  mInfoValue2->setFont(font);
  formLayout->setWidget(3, QFormLayout::FieldRole, mInfoValue2);

  mInfoValue3 = new QLabel(widget_2);
  mInfoValue3->setObjectName(QString::fromUtf8("mInfoValue3"));
  mInfoValue3->setFont(font);
  formLayout->setWidget(5, QFormLayout::FieldRole, mInfoValue3);

  mInfo1 = new QLabel(widget_2);
  mInfo1->setObjectName(QString::fromUtf8("mInfo1"));
  QFont font1;
  font1.setPointSize(8);
  font1.setBold(true);
  font1.setWeight(75);
  mInfo1->setFont(font1);
  formLayout->setWidget(1, QFormLayout::LabelRole, mInfo1);

  mInfo2 = new QLabel(widget_2);
  mInfo2->setObjectName(QString::fromUtf8("mInfo2"));
  mInfo2->setFont(font1);
  formLayout->setWidget(3, QFormLayout::LabelRole, mInfo2);

  mInfo3 = new QLabel(widget_2);
  mInfo3->setObjectName(QString::fromUtf8("mInfo3"));
  mInfo3->setFont(font1);
  formLayout->setWidget(5, QFormLayout::LabelRole, mInfo3);

  ratingBar = new KRatingWidget(mw);
  ratingBar->setGeometry(QRect(66, 45, 80, 16));
  connect(ratingBar, SIGNAL(ratingChanged(int)), SIGNAL(ratingChanged(int)));

  infoFrameSettings = new QPushButton(mw);
  infoFrameSettings->setObjectName(QString::fromUtf8("infoFrameSettings"));
  infoFrameSettings->setGeometry(QRect(198, 42, 22, 22));
  infoFrameSettings->setFlat(true);
  infoFrameSettings->setIcon(KIcon("preferences-other"));

  retranslateUi();

  //setMouseTracking(true);
}

void MediaInfoInteractivePage::retranslateUi()
{
  mInfoValue1->setText(i18n("110", 0));
  mInfoValue2->setText(i18n("7", 0));
  mInfoValue3->setText(i18n("Today", 0));
  mInfo1->setText(i18n("Score", 0));
  mInfo2->setText(i18n("Play times", 0));
  mInfo3->setText(i18n("Last play", 0));
}

void MediaInfoInteractivePage::leaveEvent(QEvent* )
{
    //QWidget::enterEvent();
    emit mouseLeave();
}

void MediaInfoInteractivePage::setMediaItem ( MediaItem* mediaItem )
{
  mInfoValue1->setText(QString::number(mediaItem->score()));
}