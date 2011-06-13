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

#ifndef YOUTUBEMANAGER_H
#define YOUTUBEMANAGER_H

//Qt
#include <QtCore/QObject>
#include <QStringList>
#include <QUrl>
#include <QString>
#include <QRegExp>
#include <QNetworkReply>
#include <QDebug>
//Playbak
#include "NetworkManager.h"

/**
 *  Search youtube videos and retrives it's streaming
 *  url. 
 **/ 
class YoutubeManager : public QObject
{
Q_OBJECT

public:
YoutubeManager();
~YoutubeManager();
/** Search some video 
 * Asynchronous.  QStringList is passed by searchFinished()
 * \param searchQuery a search query, could be title, album, etc.
 * \param resultNumber number of result, so the number of string
 * in the returned list 
 **/
void search(const QString& searchQuery, int resultNumber = 5);
/** Get the streamUrl of a video. the streamUrl is an url that 
 * points to a mpeg4 video not embed in youtube flash interface
 * Asynchronous.  QUrl is passed by gotStreamUrl
 * \param url the url that points to a normal youtube page
 * must be in this format:
 * http://www.youtube.com/watch?v=XXXXXXXXXXX
 **/
void getStreamUrl(const QString& url);

private:
  //! downloads webpages to scrap
  NetworkManager* networkManager;
  //! list of urls in QString that points to a video 
  QStringList resultList;
  //! url that points to a mpeg4 video not embed in 
  QUrl streamUrl;
  //! youtube flash interface
private slots:
  //! now find all url to videos
  void gotSearchPage();
  //! now find the streamUrl inside video_info webpage
  void  gotVideo_infoPage();
signals:
  //! videos were found
void  searchFinished(QStringList& resultList);
  //! found stream url
void  gotStreamUrl(QUrl& url);

};

#endif // YOUTUBEMANAGER_H
