<<<<<<< TREE
/*
 * PlaybaK - A KDE Multimedia Player.
 * Copyright (C) 2010 PlaybaK Development Team (see AUTHORS file)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see http://www.gnu.org/licenses
 * or write to the Free Software Foundation,Inc., 51 Franklin Street,
 * Fifth Floor, Boston, MA 02110-1301  USA
 */

=======
>>>>>>> MERGE-SOURCE
#include "MediaItem.hpp"
#include "Ontologies.hpp"

#include <Nepomuk/ResourceManager>
#include <Nepomuk/Variant>
#include <Nepomuk/Types/Class>
#include <Nepomuk/Tag>
#include <Nepomuk/Resource>
#include <Nepomuk/Tag>

#include <taglib/fileref.h>
#include <taglib/tag.h>




//#include <Nepomuk/Resour1ceManager>
#include <Nepomuk/Resource>
#include <Nepomuk/Variant>

#include <Nepomuk/Tag>

#include <Soprano/Version>
#include <Soprano/Model>
#include <Soprano/QueryResultIterator>
#include <Soprano/Node>
#include <Soprano/Statement>
#include <Soprano/LiteralValue>
#include <Soprano/StatementIterator>

MediaItem::MediaItem(KUrl url) :
  mUrl(url),
  CollectionItem(CollectionItem::Type::MIX) // TODO: Temporal
{
  // TODO: Verifi if is a valid media (image, video or music)
  //       if is not: throw
  Nepomuk::Resource rFile(url);
  Nepomuk::Variant variant;
  TagLib::FileRef id3File(url.toLocalFile().toStdString().c_str());

  // Not readed
//   mCopyrightInformationURL
  
  if ( (variant = rFile.property(NFO_FILECREATED)).isDate() )
    mCreationDate = variant.toDate();
  else if ( (variant = rFile.property(NIE_CONTENTCREATED)).isDate() )
    mCreationDate = variant.toDate();
  else
    mCreationDate = QDate();

  if ( (variant = rFile.property(NIE_KEYWORD)).isStringList() )
    mKeywords = variant.toStringList();
  else
    mKeywords = QStringList();

  if ( (variant = rFile.property(NFO_LASTUPDATED)).isDate() )
    mLastUpdate = variant.toDate();
  else if ( (variant = rFile.property(NIE_LASTUPDATE)).isDate() )
    mLastUpdate = variant.toDate();
  else
    mLastUpdate = QDate();

  if ( (variant = rFile.property(NIE_LICENSETYPE)).isString() )
    mLicense = variant.toString();
  else
    mLicense = QString();

  if ( (variant = rFile.property(NIE_MIMETYPE)).isString() )
    mMimetype = variant.toString();
  else
    mMimetype = QString();

  if ( (variant = rFile.property(NAO_SCORE)).isDouble() )
    mScore = variant.toDouble();
  else
    mScore = 0.0;

  if ( (variant = rFile.property(XESAM_RATING)).isDouble() )
    mRating = variant.toDouble();
  else if ( (variant = rFile.property(XESAM_AUTORATING)).isDouble() )
    mRating = variant.toDouble();
  else
    mRating = 0.0;

  if ( (variant = rFile.property(NAO_TAG)).isStringList() )
    mTags = variant.toStringList();
  else
    mTags = QStringList();

  // Search the correct title
  // First we search in the normal title
  // if is not, we use the id3 title (is no problem if is empty, because we have no more
  // sites to search )
  if ( (variant = rFile.property(NID3_TITLE)).isString() )
    mTitle = variant.toString();
  else if ( (variant = rFile.property(NIE_TITLE)).isString() )
    mTitle = variant.toString();
  else if ( (variant = rFile.property(XESAM_TITLE)).isString() )
    mTitle = variant.toString();
  else
    mTitle = QString();
  // We verificate with ID3 tag
  if ( !id3File.isNull() && id3File.tag()->title().toCString() != mTitle.toStdString().c_str() )
  {
    // ID3 tag is more importan than data stored in Nepomuk.
    // We use ID3 tag and update the data stored in nepomuk
    mTitle = id3File.tag()->title().toCString();
    rFile.setProperty(NID3_TITLE, Nepomuk::Variant(mTitle) );
    rFile.setProperty(NIE_TITLE, Nepomuk::Variant(mTitle) );
    // We do not save in Xesam because is depercated
  }

  // We search the year of the media in 2 sites
  // First we search in the original relase year id3 tag
  // if is not we use the recording year (is no problem if is empty, because we have no more
  // sites to search )
  if ( (variant = rFile.property(NID3_ORIGINALRELASEYEAR)).isInt() )
    mYear = variant.toInt();
  else if ( (variant = rFile.property(NID3_RECORDINGYEAR)).isInt() )
    mYear = variant.toInt();
  else if ( (variant = rFile.property(XESAM_CONTENTCREATED)).isInt() )
    mYear = variant.toInt();
  // We verificate with ID3 tag
  if ( !id3File.isNull() && id3File.tag()->year() != mYear )
  {
    // ID3 tag is more importan than data stored in Nepomuk.
    // We use ID3 tag and update the data stored in nepomuk
    mYear = id3File.tag()->year();
    rFile.setProperty(NID3_ORIGINALRELASEYEAR, Nepomuk::Variant(mYear) );
    rFile.setProperty(NID3_RECORDINGYEAR, Nepomuk::Variant(mYear) );
    // We do not save in Xesam because is depercated
  }

  // We search the audio artist
  // First we search in the lider artist
  // if is not we use the original artist (is no problem if is empty, because we have no more
  // sites to search )
  if ( (variant = rFile.property(NID3_ORIGINALARTIST)).isString() )
    mArtist = variant.toString();
  else if ( (variant = rFile.property(NIE_LEADERARTIST)).isString() )
    mArtist = variant.toString();
  else if ( (variant = rFile.property(NEXIF_ARTIST)).isString() )
    mArtist = variant.toString();
  else if ( (variant = rFile.property(XESAM_ARTIST)).isString() )
    mArtist = variant.toString();
  
  // We verificate with ID3 tag
  if ( !id3File.isNull() && id3File.tag()->artist().toCString() != mArtist.toStdString().c_str() )
  {
    // ID3 tag is more importan than data stored in Nepomuk.
    // We use ID3 tag and update the data stored in nepomuk
    mArtist = id3File.tag()->artist().toCString();
    // If is an audio or video we update the ID3 tag
    if ((bool)(mMimetype.contains("audio",Qt::CaseInsensitive)) | (bool)(mMimetype.contains("video",Qt::CaseInsensitive)) )
    {
      rFile.setProperty(NID3_ORIGINALARTIST, Nepomuk::Variant(mArtist) );
      rFile.setProperty(NIE_LEADERARTIST, Nepomuk::Variant(mArtist) );
    }
    else if (mMimetype.contains("image") )
    {
      rFile.setProperty(NEXIF_ARTIST, Nepomuk::Variant(mArtist) );
    }
    // We do not save in Xesam because is depercated
  }
}

QString MediaItem::artist()
{
  return mArtist;
}

KUrl MediaItem::copyrightInformationURL()
{
  return mCopyrightInformationURL;
}

QDate MediaItem::creationDate()
{
  return mCreationDate;
}

qint64 MediaItem::fileSize()
{
  return mFileSize;
}

int MediaItem::id()
{
  return mId;
}

QStringList MediaItem::keywords()
{
  return mKeywords;
}

QDate MediaItem::lastUpdate()
{
  return mLastUpdate;
}

QString MediaItem::license()
{
  return mLicense;
}

QString MediaItem::mimetype()
{
  return mMimetype;
}

double MediaItem::score()
{
  return mScore;
}

double MediaItem::rating()
{
  return mRating;
}

QMap<QString,int> MediaItem::similarsArtists()
{
  return mSimilarArtists;
}

QMap<QString,int> MediaItem::similarsMedias()
{
  return mSimilarMedias;
}

QStringList MediaItem::tags()
{
  return mTags;
}

QString MediaItem::title()
{
  return mTitle;
}

KUrl MediaItem::url()
{
  return mUrl;
}

int MediaItem::year()
{
  return mYear;
}


bool MediaItem::hasKeyword(QString keyword)
{
  return mKeywords.contains(keyword);
}

bool MediaItem::hasSimilarArtist(QString similarsArtists)
{
  return mSimilarArtists.contains(similarsArtists);
}

bool MediaItem::hasSimilarMedia(QString mediaName)
{
  return mSimilarMedias.contains(mediaName);
}
void MediaItem::addKeyword(QString keyword)
{
  // Load the resource
  Nepomuk::Resource rFile(mUrl.toLocalFile().toStdString().c_str());
  // Add the keyword
  mKeywords << keyword;
  // Update Nepomuk
  rFile.setProperty(NIE_KEYWORD, Nepomuk::Variant(mKeywords));
}

void MediaItem::removeKeyword(QString keyword)
{
  // Load the resource
  Nepomuk::Resource rFile(mUrl.toLocalFile().toStdString().c_str());
  // remove the keyword
  mKeywords.removeAll(keyword);
  // Update Nepomuk
  rFile.setProperty(NIE_KEYWORD, Nepomuk::Variant(mKeywords));
}

void MediaItem::addSimilarArtist(QString artistName, int percentage)
{
  mSimilarArtists[artistName] = percentage;
  // TODO: Update Nepomuk
}

void MediaItem::addSimilarMedia(QString mediaName, int percentage)
{
  mSimilarMedias[mediaName] = percentage;
  // TODO: Update Nepomuk
}

void MediaItem::removeSimilarArtist(QString artistName)
{
  mSimilarArtists.remove(artistName);
  // TODO: Update Nepomuk
}

void MediaItem::removeSimilarMedia(QString mediaName)
{
  mSimilarMedias.remove(mediaName);
  // TODO: Update Nepomuk
}

void MediaItem::addTag(QString tag)
{
  // Load the resource
  Nepomuk::Resource rFile(mUrl.toLocalFile().toStdString().c_str());
  // Add the tag
  mTags << tag;
  // Update Nepomuk
  rFile.setProperty(NAO_TAG, Nepomuk::Variant(mTags));
}

void MediaItem::setArtist(QString artist)
{
  // Load the resource
  Nepomuk::Resource rFile(mUrl.toLocalFile().toStdString().c_str());
  TagLib::FileRef id3File(mUrl.toLocalFile().toStdString().c_str());
  // Rewrite the artist
  mArtist = artist;
  // Update Nepomuk
  // If is an audio or video we update the ID3 tag
  if ((bool)(mMimetype.contains("audio",Qt::CaseInsensitive)) | (bool)(mMimetype.contains("video",Qt::CaseInsensitive)) )
  {
    rFile.setProperty(NID3_ORIGINALARTIST, Nepomuk::Variant(mArtist));
    rFile.setProperty(NIE_LEADERARTIST, Nepomuk::Variant(mArtist));
    
    id3File.tag()->setArtist(mArtist.toStdString().c_str());
  }
  // If is an image
  else if (mMimetype.contains("image") )
  {
    rFile.setProperty(NEXIF_ARTIST, Nepomuk::Variant(mArtist) );
    // TODO: Update the image tag file
  }
}

void MediaItem::setCopyrightInformationURL(KUrl url)
{
  mCopyrightInformationURL = url;
  // TODO: Update Nepomuk
}

void MediaItem::setCreationDate(QDate creationDate)
{
  // Load the resource
  Nepomuk::Resource rFile(mUrl.toLocalFile().toStdString().c_str());
  // Set creation date
  mCreationDate = creationDate;
  // Update Nepomuk
  rFile.setProperty(NFO_FILECREATED, Nepomuk::Variant(mCreationDate));
  rFile.setProperty(NIE_CONTENTCREATED, Nepomuk::Variant(mCreationDate));
}

void MediaItem::setId(int id)
{
  // TODO
}

void MediaItem::setKeywords(QStringList keywords)
{
  // Load the resource
  Nepomuk::Resource rFile(mUrl.toLocalFile().toStdString().c_str());
  mKeywords = keywords;
  // Set the keywords
  rFile.setProperty(NIE_KEYWORD, Nepomuk::Variant(mKeywords));
}

void MediaItem::setLastUpdate(QDate lastUpdate)
{
  // Load the resource
  Nepomuk::Resource rFile(mUrl.toLocalFile().toStdString().c_str());
  mLastUpdate = lastUpdate;
  // Set last update
  rFile.setProperty(NFO_LASTUPDATED, Nepomuk::Variant(mLastUpdate));
  rFile.setProperty(NIE_LASTUPDATE, Nepomuk::Variant(mLastUpdate));
}

void MediaItem::setLicense(QString license)
{
  // Load the resource
  Nepomuk::Resource rFile(mUrl.toLocalFile().toStdString().c_str());
  mLicense = license;
  // Set the license
  rFile.setProperty(NIE_LICENSETYPE, Nepomuk::Variant(mLicense));
}

void MediaItem::setMimetype(QString mimetype)
{
  // Load the resource
  Nepomuk::Resource rFile(mUrl.toLocalFile().toStdString().c_str());
  mMimetype = mimetype;
  // Set the mime type
  rFile.setProperty(NIE_MIMETYPE, Nepomuk::Variant(mMimetype));
}

void MediaItem::setScore(double score)
{
  // Load the resource
  Nepomuk::Resource rFile(mUrl.toLocalFile().toStdString().c_str());
  mScore = score;
  // Set the score
  rFile.setProperty(NAO_SCORE, Nepomuk::Variant(mScore));
}

void MediaItem::setRating(double rating)
{
  // Load the resource
  Nepomuk::Resource rFile(mUrl.toLocalFile().toStdString().c_str());
  mRating = rating;
  // Set the rating
  rFile.setProperty(NAO_SCORE, Nepomuk::Variant(rating));
}

void MediaItem::setSimilarArtists(QMap<QString,int> similarArtist)
{
  // Load the resource
  Nepomuk::Resource rFile(mUrl.toLocalFile().toStdString().c_str());
  mSimilarArtists = similarArtist;
  // Set the rating
  // TODO
//   rFile.setProperty(/* TODO */, Nepomuk::Variant(mSimilarArtists));
}

void MediaItem::setSimilarMedias(QMap<QString,int> similarMedias)
{
  // Load the resource
  Nepomuk::Resource rFile(mUrl.toLocalFile().toStdString().c_str());
  mSimilarMedias = similarMedias;
  // Set the rating
  // TODO
  //   rFile.setProperty(/* TODO */, Nepomuk::Variant(mSimilarMedias));
}

void MediaItem::setTags(QStringList tags)
{
  // Load the resource
  Nepomuk::Resource rFile(mUrl.toLocalFile().toStdString().c_str());
  mTags = tags;
  // Set the rating
  rFile.setProperty(NAO_TAG, Nepomuk::Variant(mTags));
}

void MediaItem::setTitle(int title)
{
  // Load the resource
  Nepomuk::Resource rFile(mUrl.toLocalFile().toStdString().c_str());
  TagLib::FileRef id3File(mUrl.toLocalFile().toStdString().c_str());
  mTitle = title;
  // Set the rating
  rFile.setProperty(NIE_TITLE, Nepomuk::Variant(mTitle));
  rFile.setProperty(NID3_TITLE, Nepomuk::Variant(mTitle));
  id3File.tag()->setTitle(mTitle.toStdString().c_str());
}

void MediaItem::setUrl(KUrl url)
{
  // TODO
}

void MediaItem::setYear(int year)
{
  // Load the resource
  Nepomuk::Resource rFile(mUrl.toLocalFile().toStdString().c_str());
  TagLib::FileRef id3File(mUrl.toLocalFile().toStdString().c_str());
  mYear = year;
  // Set the rating
  rFile.setProperty(NID3_ORIGINALRELASEYEAR, Nepomuk::Variant(mTitle));
  rFile.setProperty(NID3_RECORDINGYEAR, Nepomuk::Variant(mTitle));
  id3File.tag()->setYear(mYear);
}