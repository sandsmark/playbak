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

#include "YoutubeManager.h"

YoutubeManager::YoutubeManager() : resultList(0), streamUrl(0)
{
  networkManager = NetworkManager::networkManagerInstance();
}

YoutubeManager::~YoutubeManager()
{
  
}

void YoutubeManager::search(const QString& searchQuery, int resultNumber)
{
  // Clean query, replace non alphanumeric character with +
  QRegExp regExp;
  regExp.setPattern("[^A-Za-z0-9]+");
  QString query = searchQuery;
  query = query.replace(regExp,"+");
  QNetworkRequest searchRequest;
  searchRequest.setUrl(QString(
    "http://gdata.youtube.com/feeds/api/videos?q=%1&max-results=%2").arg(
      query, QString::number(resultNumber)));
  QNetworkReply *reply = networkManager->get(searchRequest);
  connect(reply, SIGNAL(finished()), this, SLOT(gotSearchPage()));
  
}

void YoutubeManager::getStreamUrl(const QString& url)
{
  //is the unique id of a video
  QString videoID;
  //check url format
  if (!url.startsWith("http://www.youtube.com/watch?v=")) {
    qDebug() << 
    "wrong url, must be in this format http://www.youtube.com/watch?v=XXXXXXXXXXX"
    << endl << "it was " << url << endl;
    return;
  }
  //copy video id
  videoID = url.mid(31,11);
  qDebug() << "videoID: " << videoID << endl;
  //continues in gotVideo_infoPage
  QNetworkRequest video_infoRequest;
  video_infoRequest.setUrl(QString(
    "http://www.youtube.com/get_video_info?video_id=").append(videoID));
  
  QNetworkReply *reply = networkManager->get(video_infoRequest);
  connect(reply, SIGNAL(finished()), this, SLOT(gotVideo_infoPage()));
  
}

void YoutubeManager::gotSearchPage()
{
  //erase precedents result
  resultList.clear();
  // a normal link to a youtube video
  QRegExp regExp("http://www.youtube.com/watch\\?v=\\w{11,11}");
  //the webpage to scrap
  QNetworkReply * reply =  qobject_cast<QNetworkReply*>(sender());
  QString searchPage = reply->readAll();
  int offset = 0;
  int skipOdds = 0;
  while (offset > -1) {
    // go further
    offset++;
    offset = regExp.indexIn(searchPage,offset);
    //since links repeats twice, skip odds number of time
    skipOdds++;
    if (skipOdds%2) continue;
    resultList.append(regExp.cap(0));
  }
  //qDebug() << " resultList: " << resultList.join("\n") << endl;
  emit searchFinished(resultList);
}

void YoutubeManager::gotVideo_infoPage()
{
  //TODO: rewrite this stuff whith regEx?
  QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
  QString video_infoPage = QUrl::fromPercentEncoding(
    reply->readAll());
  int lastLinkIndex = video_infoPage.indexOf("videoplayback");
  int urlStart = video_infoPage.lastIndexOf("http",lastLinkIndex);
  int urlEnd = video_infoPage.indexOf("|",urlStart);
  streamUrl.setUrl(video_infoPage.mid(urlStart,urlEnd-urlStart));
  //qDebug() << "streamUrl: " << streamUrl << endl;
  emit gotStreamUrl(streamUrl);
}



