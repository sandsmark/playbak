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

#include <omp.h>

#include <taglib/fileref.h>
#include <taglib/tag.h>

#include <QEventLoop>
#include <QImage>
#include <QThread>

#include <KDE/KMimeType>

#include <Nepomuk/Resource>
#include <Nepomuk/ResourceManager>
#include <Nepomuk/Tag>
#include <Nepomuk/Types/Class>
#include <Nepomuk/Variant>

#include <Phonon/MediaObject>

#include <MediaItem.h>
#include <Ontologies.h>

MediaItem::MediaItem(const MediaItem& copy): CollectionItem(CollectionItem::Type::MIX) //CollectionItem(copy)
{
  mByDemand = copy.mByDemand;
  mUrl      = copy.mUrl;
  rFile     = 0x0L;
  variant   = 0x0L;
  id3File   = 0x0L;

  if (mByDemand)
  {
    mYear = 0;
    mScore = mRating = 0.0;
    firstConstructMediaItem();
    return;
  }

  mArtist = copy.mArtist;
  mCopyrightInformationURL = copy.mCopyrightInformationURL;
  mCreationDate = copy.mCreationDate;
  mFileSize     = copy.mFileSize;
  mId           = copy.mId;
  mKeywords     = copy.mKeywords;
  mLastUpdate   = copy.mLastUpdate;
  mLicense      = copy.mLicense;
  mMimetype     = copy.mMimetype;
  mRating       = copy.mRating;
  mScore        = copy.mScore;
  mSimilarArtists = copy.mSimilarArtists;
  mSimilarMedias  = copy.mSimilarMedias;
  mTags  = copy.mTags;
  mTitle = copy.mTitle;
  mYear  = copy.mYear;
}

MediaItem::MediaItem(KUrl url, bool byDemand) :
  mUrl(url),
  CollectionItem(CollectionItem::Type::MIX) // TODO: Temporal el MIX
{
  mByDemand = byDemand;
  mYear = 0;
  mScore = mRating = 0.0;

  rFile = 0x0L;
  variant = 0x0L;
  id3File = new TagLib::FileRef(mUrl.toLocalFile().toUtf8());;
  
  firstConstructMediaItem();
}

void MediaItem::firstConstructMediaItem()
{
  if (mByDemand)
  {
    rFile = new Nepomuk::Resource(mUrl);
    variant = new Nepomuk::Variant;
    id3File = new TagLib::FileRef(mUrl.toLocalFile().toUtf8());
  }
  else
    loadMediaItemMetadata();
}

// NOTE Read the datas in parallel
void MediaItem::loadMediaItemMetadata()
{
  if(!mByDemand)
  {
    rFile = new Nepomuk::Resource(mUrl);
    variant = new Nepomuk::Variant;
    id3File = new TagLib::FileRef(mUrl.toLocalFile().toUtf8());
  }

  // TODO: Verify if is a valid media (image, video or music)
  //       if is not: throw
  
  //! We verify is Nepomuk was initialized (is recomended if we use thread, and we use it)
  if (rFile->manager()->initialized())
    rFile->manager()->init();

  //! Load the media's creation date.
  if ( (*variant = rFile->property(NAO_CREATED)).isValid() )
    mCreationDate = variant->toDate();
  else if ( (*variant = rFile->property(NFO_FILECREATED)).isValid() )
    mCreationDate = variant->toDate();
  else if ( (*variant = rFile->property(NIE_CONTENTCREATED)).isValid() )
    mCreationDate = variant->toDate();
  else
    mCreationDate = QDate();

  //! Load the media's keywords.
  if ( (*variant = rFile->property(NIE_KEYWORD)).isValid() )
    mKeywords = variant->toStringList();
  else
    mKeywords = QStringList();

  //! Load the media's last update date.
  if ( (*variant = rFile->property(NFO_LASTUPDATED)).isValid() )
    mLastUpdate = variant->toDate();
  else if ( (*variant = rFile->property(NIE_LASTUPDATE)).isValid() )
    mLastUpdate = variant->toDate();
  else
    mLastUpdate = QDate();

  //! Load the media's license.
  if (mLicense.isEmpty())
    if ( (*variant = rFile->property(NIE_LICENSETYPE)).isValid() )
      mLicense = variant->toString();
    else
      mLicense = QString();

  //! Load the media's mimetype.
  if ( !(*variant = rFile->property(NIE_MIMETYPE)).toString().isEmpty() ) {
    mMimetype = variant->toString();
  } else { //! If has not mimetype, we set manually the mimetype, because is necesary
    //! Load the media with Phonon to try to detect the media type.
    Phonon::MediaObject *media = new Phonon::MediaObject();
    media->setCurrentSource(Phonon::MediaSource(mUrl));
    if (media->isValid())
    {
      //! We wait to finish to read
      QEventLoop loop;
      QObject::connect(media, SIGNAL(stateChanged(Phonon::State,Phonon::State)), &loop, SLOT(quit()));
      loop.exec();

      if (media->hasVideo())
        setMimetype("video/"); // TODO: load the full mimetype
      else
        setMimetype("audio/"); // TODO: load the full mimetype
    }
    else
    {
      QImage img;
      img.load(mUrl.toLocalFile());

      if (!img.isNull())
        setMimetype("image/"); // TODO: load the full mimetype
    }
    delete media;
  }

  //! Load the media's score.
  if ( (*variant = rFile->property(NAO_SCORE)).isValid() )
    mScore = variant->toDouble();
  else
    mScore = 0.0;

  //! Load the media's rating.
  if ( (*variant = rFile->property(XESAM_RATING)).isValid() )
    mRating = variant->toDouble();
  else if ( (*variant = rFile->property(XESAM_AUTORATING)).isValid() )
    mRating = variant->toDouble();
  else
    mRating = 0.0;

  //! Load the media's tags.
  if ( (*variant = rFile->property(NAO_TAG)).isValid() )
    mTags = variant->toStringList();
  else
    mTags = QStringList();

  //! Load the media's title.
  //BEGIN
  if (mTitle.isEmpty())
    if ( (*variant = rFile->property(NID3_TITLE)).isValid() )
      mTitle = variant->toString();
    else if ( (*variant = rFile->property(NIE_TITLE)).isValid() )
      mTitle = variant->toString();
    else if ( (*variant = rFile->property(XESAM_TITLE)).isValid() )
      mTitle = variant->toString();

  //! We try with ID3 tag.
  if (mTitle.isEmpty())
    if ( !id3File->isNull() && id3File->tag()->title().toCString() != mTitle.toStdString().c_str() )
    {
      // ID3 tag is more importan than data stored in Nepomuk.
      // We use ID3 tag and update the data stored in nepomuk
      mTitle = id3File->tag()->title().toCString();
      rFile->setProperty(NID3_TITLE, Nepomuk::Variant(mTitle) );
      rFile->setProperty(NIE_TITLE, Nepomuk::Variant(mTitle) );
      // We do not save in Xesam because is depercated
    }
  //END

  //! Load the media's year.
  //BEGIN
  if (mYear == 0)
  {
    if ( (*variant = rFile->property(NID3_ORIGINALRELASEYEAR)).isValid() )
      mYear = variant->toInt();
    else if ( (*variant = rFile->property(NID3_RECORDINGYEAR)).isValid() )
      mYear = variant->toInt();
    else if ( (*variant = rFile->property(XESAM_CONTENTCREATED)).isValid() )
      mYear = variant->toInt();
  }

  //! We try with ID3 tag.
  if (mYear == 0)
    if ( !id3File->isNull() && id3File->tag()->year() != mYear )
    {
      //! ID3 tag is more importan than data stored in Nepomuk.
      
      //! We use ID3 tag and update the data stored in Nepomuk.
      mYear = id3File->tag()->year();
      rFile->setProperty(NID3_ORIGINALRELASEYEAR, Nepomuk::Variant(mYear) );
      rFile->setProperty(NID3_RECORDINGYEAR, Nepomuk::Variant(mYear) );
      //! NOTE We do not save in Xesam because is depercated.
    }
  //END

  //! Load the media's artist.
  //BEGIN
  if (mArtist.isEmpty())
    if ( (*variant = rFile->property(NID3_ORIGINALARTIST)).isValid() )
      mArtist = variant->toString();
    else if ( (*variant = rFile->property(NIE_LEADERARTIST)).isValid() )
      mArtist = variant->toString();
    else if ( (*variant = rFile->property(NEXIF_ARTIST)).isValid() )
      mArtist = variant->toString();
    else if ( (*variant = rFile->property(XESAM_ARTIST)).isValid() )
      mArtist = variant->toString();
    
  
  //! We try with ID3 tag.
  if ( !id3File->isNull() && id3File->tag()->artist().toCString() != mArtist.toStdString().c_str() )
  {
    //! ID3 tag is more importan than data stored in Nepomuk.
    
    //! We use ID3 tag and update the data stored in Nepomuk.
    mArtist = id3File->tag()->artist().toCString();
    
    //! If is an audio or video we update the ID3 tag
    if ((bool)(mMimetype.contains("audio",Qt::CaseInsensitive)) | (bool)(mMimetype.contains("video",Qt::CaseInsensitive)) )
    {
      rFile->setProperty(NID3_ORIGINALARTIST, Nepomuk::Variant(mArtist) );
      rFile->setProperty(NIE_LEADERARTIST, Nepomuk::Variant(mArtist) );
    }
    else if (mMimetype.contains("image") )
    {
      rFile->setProperty(NEXIF_ARTIST, Nepomuk::Variant(mArtist) );
    }
    //! NOTE We do not save in Xesam because is depercated.
  }
  //END

  //! When we load all metadatas, is no more necesary use mByDemand
  mByDemand = false;
  
  delete rFile;
  delete variant;
  delete id3File;
  
  rFile = 0x0L;
  variant = 0x0L;
  id3File = 0x0L;
    
  emit metadataChanged();
}

QString MediaItem::artist()
{
  if (mByDemand && mArtist.isNull())
  {
    if (id3File->isNull() )
      return QString();
    
    mArtist = id3File->tag()->artist().toCString();
    if (mArtist.isEmpty()) {
      if ( (*variant = rFile->property(NID3_ORIGINALARTIST)).isValid() )
        mArtist = variant->toString();
      else if ( (*variant = rFile->property(NIE_LEADERARTIST)).isValid() )
        mArtist = variant->toString();
      else if ( (*variant = rFile->property(NEXIF_ARTIST)).isValid() )
        mArtist = variant->toString();
      else if ( (*variant = rFile->property(XESAM_ARTIST)).isValid() )
        mArtist = variant->toString();
    }
  }
  return mArtist;
}

KUrl MediaItem::copyrightInformationURL()
{
  if (mByDemand && mCopyrightInformationURL.isEmpty())
  {
      // TODO
  }
  return mCopyrightInformationURL;
}

QDate MediaItem::creationDate()
{
  if (mByDemand && mCreationDate.isNull())
  {
    if ( (*variant = rFile->property(NAO_CREATED)).isValid() )
      mCreationDate = variant->toDate();
    else if ( (*variant = rFile->property(NFO_FILECREATED)).isValid() )
      mCreationDate = variant->toDate();
    else if ( (*variant = rFile->property(NIE_CONTENTCREATED)).isValid() )
      mCreationDate = variant->toDate();
    else
      mCreationDate = QDate();
  }
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
  if (mByDemand && mKeywords.isEmpty())
  {
    if ( (*variant = rFile->property(NIE_KEYWORD)).isValid() )
      mKeywords = variant->toStringList();
    else
      mKeywords = QStringList();
  }
  return mKeywords;
}

QDate MediaItem::lastUpdate()
{
  if (mByDemand && mLastUpdate.isNull())
  {
    if ( (*variant = rFile->property(NFO_LASTUPDATED)).isValid() )
      mLastUpdate = variant->toDate();
    else if ( (*variant = rFile->property(NIE_LASTUPDATE)).isValid() )
      mLastUpdate = variant->toDate();
  }
  return mLastUpdate;
}

QString MediaItem::license()
{
  if (mByDemand && mLicense.isEmpty())
  {
    if (mLicense.isEmpty())
    {
      if ( (*variant = rFile->property(NIE_LICENSETYPE)).isValid() )
        mLicense = variant->toString();
      else
        mLicense = QString();
    }
  }
  return mLicense;
}

QString MediaItem::mimetype()
{
  if (mByDemand && mMimetype.isEmpty())
  {
    KMimeType::Ptr mime = KMimeType::findByUrl(mUrl,0,false,true);
    mMimetype = mime->name().toAscii();
    mime.clear();
    if (!mMimetype.isEmpty())
      return mMimetype;
    
    if ( !(*variant = rFile->property(NIE_MIMETYPE)).toString().isEmpty() )
    {
      mMimetype = variant->toString();
    } else { //! If has not mimetype, we set manualy the mimetype, because is necessary.
      //! Load the media with Phonon to try to detect the type.
      Phonon::MediaObject *media = new Phonon::MediaObject();
      media->setCurrentSource(Phonon::MediaSource(mUrl));
      if (media->isValid())
      {
        //! We wait to finish to read.
        QEventLoop loop;
        QObject::connect(media, SIGNAL(stateChanged(Phonon::State,Phonon::State)), &loop, SLOT(quit()));
        loop.exec();
        
        if (media->hasVideo())
          setMimetype("video/");
          else
            setMimetype("audio/");
      }
      else
      {
        QImage img;
        img.load(mUrl.toLocalFile());
        if (!img.isNull())
          setMimetype("image/");
      }
      delete media;
    }
  }
  return mMimetype;
}

double MediaItem::score()
{
  if (mByDemand && (mScore != 0.0))
  {
    if ( (*variant = rFile->property(NAO_SCORE)).isValid() )
      mScore = variant->toDouble();
    else
      mScore = 0.0;
  }
  return mScore;
}

double MediaItem::rating()
{
  if (mByDemand && (mRating != 0.0))
  {
    if ( (*variant = rFile->property(XESAM_RATING)).isValid() )
      mRating = variant->toDouble();
    else if ( (*variant = rFile->property(XESAM_AUTORATING)).isValid() )
      mRating = variant->toDouble();
    else
      mRating = 0.0;
  }
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
  if (mByDemand && mTags.isEmpty())
  {
    if ( (*variant = rFile->property(NAO_TAG)).isValid() )
      mTags = variant->toStringList();
  }
  return mTags;
}

QString MediaItem::title()
{
  if (mByDemand && mTitle.isEmpty())
  {
    if ( (mTitle.isEmpty())  )
    {
      if ( !id3File->isNull() && id3File->tag()->title().toCString() != mTitle.toStdString().c_str() ) {
        //! ID3 tag is more importan than data stored in Nepomuk.
        
        //! We use ID3 tag and update the data stored in Nepomuk.
        mTitle = id3File->tag()->title().toCString();
        rFile->setProperty(NID3_TITLE, Nepomuk::Variant(mTitle) );
        rFile->setProperty(NIE_TITLE, Nepomuk::Variant(mTitle) );

        if (!mTitle.isEmpty())
          return mTitle;

        //! NOTE We do not save in Xesam because is depercated.
      }
    }

    if (mTitle.isEmpty()){
      if ( (*variant = rFile->property(NID3_TITLE)).isValid() )
        mTitle = variant->toString();
      else if ( (*variant = rFile->property(NIE_TITLE)).isValid() )
        mTitle = variant->toString();
      else if ( (*variant = rFile->property(XESAM_TITLE)).isValid() )
        mTitle = variant->toString();
    }
  }
  return mTitle;
}

KUrl MediaItem::url() const
{
  return mUrl;
}

int MediaItem::year()
{
  if (mByDemand && mTags.isEmpty())
  {
    //! Load the media's year.
    if ( (*variant = rFile->property(NID3_ORIGINALRELASEYEAR)).isValid() )
      mYear = variant->toInt();
    else if ( (*variant = rFile->property(NID3_RECORDINGYEAR)).isValid() )
      mYear = variant->toInt();
    else if ( (*variant = rFile->property(XESAM_CONTENTCREATED)).isValid() )
      mYear = variant->toInt();
    
    
    //! We try with ID3 tag.
    if (mYear == 0)
      if ( !id3File->isNull() && id3File->tag()->year() != mYear )
      {
        //! ID3 tag is more importan than data stored in Nepomuk.
        
        //! We use ID3 tag and update the data stored in Nepomuk
        mYear = id3File->tag()->year();
        rFile->setProperty(NID3_ORIGINALRELASEYEAR, Nepomuk::Variant(mYear) );
        rFile->setProperty(NID3_RECORDINGYEAR, Nepomuk::Variant(mYear) );
        
        //! NOTE We do not save in Xesam because is depercated
      }
  }
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
  if(!mByDemand)
  {
    rFile = new Nepomuk::Resource(mUrl);
  }
  mKeywords << keyword;
  
  //! Update Nepomuk.
  rFile->setProperty(NIE_KEYWORD, Nepomuk::Variant(mKeywords));
  if(!mByDemand)
  {
    delete rFile;
    rFile = 0x0L;
  }
}

void MediaItem::removeKeyword(QString keyword)
{
  if(!mByDemand)
  {
    rFile = new Nepomuk::Resource(mUrl);
  }
  
  // remove the keyword
  mKeywords.removeAll(keyword);
  // Update Nepomuk
  rFile->setProperty(NIE_KEYWORD, Nepomuk::Variant(mKeywords));
  if(!mByDemand)
  {
    delete rFile;
    rFile = 0x0L;
  }
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
  if(!mByDemand)
  {
    rFile = new Nepomuk::Resource(mUrl);
  }
  mTags << tag;
  
  //! Update metadata.
  rFile->setProperty(NAO_TAG, Nepomuk::Variant(mTags));
  if(!mByDemand)
  {
    delete rFile;
    rFile = 0x0L;
  }
}

void MediaItem::setArtist(QString artist)
{
  if(!mByDemand)
  {
    rFile = new Nepomuk::Resource(mUrl);
    id3File = new TagLib::FileRef(mUrl.toLocalFile().toUtf8());
  }
  //! Rewrite the artist
  mArtist = artist;
  
  //! Update metadata.
  if ((bool)(mMimetype.contains("audio",Qt::CaseInsensitive)) | (bool)(mMimetype.contains("video",Qt::CaseInsensitive)) )
  {
    if (rFile->property(NID3_ORIGINALARTIST).isValid())
      rFile->setProperty(NID3_ORIGINALARTIST, Nepomuk::Variant(mArtist));
    else
      rFile->addProperty(NID3_ORIGINALARTIST, Nepomuk::Variant(mArtist));

    if (rFile->property(NIE_LEADERARTIST).isValid())
      rFile->setProperty(NIE_LEADERARTIST, Nepomuk::Variant(mArtist));
    else
      rFile->addProperty(NIE_LEADERARTIST, Nepomuk::Variant(mArtist));
    
    id3File->tag()->setArtist(mArtist.toStdString().c_str());
  }
  else if (mMimetype.contains("image") )
  {
    if (rFile->property(NEXIF_ARTIST).isValid())
      rFile->setProperty(NEXIF_ARTIST, Nepomuk::Variant(mArtist));
    else
      rFile->addProperty(NEXIF_ARTIST, Nepomuk::Variant(mArtist));
    // TODO: Update the image tag file
  }

  if(!mByDemand)
  {
    delete rFile;
    delete id3File;
    rFile = 0x0L;
    id3File = 0x0L;
  }
}

void MediaItem::setCopyrightInformationURL(KUrl url)
{
  mCopyrightInformationURL = url;
  // TODO: Update Nepomuk
}

void MediaItem::setCreationDate(QDate creationDate)
{
  if(!mByDemand)
  {
    rFile = new Nepomuk::Resource(mUrl);
  }
  //! Set the creation date.
  
  mCreationDate = creationDate;
  
  //! Update metadata.
  if (rFile->property(NFO_FILECREATED).isValid())
    rFile->setProperty(NFO_FILECREATED, Nepomuk::Variant(mCreationDate));
  else
    rFile->addProperty(NFO_FILECREATED, Nepomuk::Variant(mCreationDate));

  if (rFile->property(NIE_CONTENTCREATED).isValid())
    rFile->setProperty(NIE_CONTENTCREATED, Nepomuk::Variant(mCreationDate));
  else
    rFile->addProperty(NIE_CONTENTCREATED, Nepomuk::Variant(mCreationDate));

  if(!mByDemand)
  {
    delete rFile;
    rFile = 0x0L;
  }
}

void MediaItem::setId(int id)
{
  // TODO
}

void MediaItem::setKeywords(QStringList keywords)
{
  if(!mByDemand)
  {
    rFile = new Nepomuk::Resource(mUrl);
  }
  //! Set the keywords.
  mKeywords = keywords;

  //! Update metadata.
  if (rFile->property(NIE_KEYWORD).isValid())
    rFile->setProperty(NIE_KEYWORD, Nepomuk::Variant(mKeywords));
  else
    rFile->addProperty(NIE_KEYWORD, Nepomuk::Variant(mKeywords));
  
  if(!mByDemand)
  {
    delete rFile;
    rFile = 0x0L;
  }
}

void MediaItem::setLastUpdate(QDate lastUpdate)
{
  if(!mByDemand)
  {
    rFile = new Nepomuk::Resource(mUrl);
  }
  
  //! Set the last update date.
  mLastUpdate = lastUpdate;

  //! Update metadata.
  //BEGIN
  if (rFile->property(NFO_LASTUPDATED).isValid())
    rFile->setProperty(NFO_LASTUPDATED, Nepomuk::Variant(mLastUpdate));
  else
    rFile->addProperty(NFO_LASTUPDATED, Nepomuk::Variant(mLastUpdate));

  if (rFile->property(NIE_LASTUPDATE).isValid())
    rFile->setProperty(NIE_LASTUPDATE, Nepomuk::Variant(mLastUpdate));
  else
    rFile->addProperty(NIE_LASTUPDATE, Nepomuk::Variant(mLastUpdate));
  //END

  if(!mByDemand)
  {
    delete rFile;
    rFile = 0x0L;
  }
}

void MediaItem::setLicense(QString license)
{
  if(!mByDemand)
  {
    rFile = new Nepomuk::Resource(mUrl);
  }

  //! Set the license.
  mLicense = license;

  //! Update metadata.
  if (rFile->property(NIE_LICENSETYPE).isValid())
    rFile->setProperty(NIE_LICENSETYPE, Nepomuk::Variant(mLicense));
  else
    rFile->addProperty(NIE_LICENSETYPE, Nepomuk::Variant(mLicense));

  if(!mByDemand)
  {
    delete rFile;
    rFile = 0x0L;
  }
}

void MediaItem::setMimetype(QString mimetype)
{
  if(!mByDemand)
  {
    rFile = new Nepomuk::Resource(mUrl);
  }

  //! Set the mimetype.
  mMimetype = mimetype;

  //! Update metadata.
  if (rFile->property(NIE_MIMETYPE).isValid())
      rFile->setProperty(NIE_MIMETYPE, Nepomuk::Variant(mMimetype));
  else
    rFile->addProperty(NIE_MIMETYPE, Nepomuk::Variant(mMimetype));

  if(!mByDemand)
  {
    delete rFile;
    rFile = 0x0L;
  }
}

void MediaItem::setScore(double score)
{
  if(!mByDemand)
  {
    rFile = new Nepomuk::Resource(mUrl);
  }

  //! Set the score.
  mScore = score;

  //! Update metadata.
  if (rFile->property(NAO_SCORE).isValid())
    rFile->setProperty(NAO_SCORE, Nepomuk::Variant(mScore));
  else
    rFile->addProperty(NAO_SCORE, Nepomuk::Variant(mScore));

  if(!mByDemand)
  {
    delete rFile;
    rFile = 0x0L;
  }
}

void MediaItem::setRating(double rating)
{
  if(!mByDemand)
  {
    rFile = new Nepomuk::Resource(mUrl);
  }

  //! Set the rating.
  mRating = rating;

  //! Update metadata.
  //BEGIN
  if (rFile->property(XESAM_RATING).isValid())
    rFile->setProperty(XESAM_RATING, Nepomuk::Variant(mRating));
  else
    rFile->addProperty(XESAM_RATING, Nepomuk::Variant(mRating));

  if (rFile->property(XESAM_AUTORATING).isValid())
    rFile->setProperty(XESAM_AUTORATING, Nepomuk::Variant(mRating));
  else
    rFile->addProperty(XESAM_AUTORATING, Nepomuk::Variant(mRating));
  //END

  if(!mByDemand)
  {
    delete rFile;
    rFile = 0x0L;
  }
}

void MediaItem::setSimilarArtists(QMap<QString,int> similarArtist)
{  
  mSimilarArtists = similarArtist;
  // Set the rating
  // TODO
//   rFile->setProperty(/* TODO */, Nepomuk::Variant(mSimilarArtists));
}

void MediaItem::setSimilarMedias(QMap<QString,int> similarMedias)
{  
  mSimilarMedias = similarMedias;
  // Set the rating
  // TODO
  //   rFile->setProperty(/* TODO */, Nepomuk::Variant(mSimilarMedias));
}

void MediaItem::setTags(QStringList tags)
{
  if(!mByDemand)
  {
    rFile = new Nepomuk::Resource(mUrl);
  }

  //! Set the tags.
  mTags = tags;

  //! Update metadata.
  if (rFile->property(NAO_TAG).isValid())
    rFile->setProperty(NAO_TAG, Nepomuk::Variant(mTags));
  else
    rFile->addProperty(NAO_TAG, Nepomuk::Variant(mTags));

  if(!mByDemand)
  {
    delete rFile;
    rFile = 0x0L;
  }
}

void MediaItem::setTitle(int title)
{
  if(!mByDemand)
  {
    rFile = new Nepomuk::Resource(mUrl);
    id3File = new TagLib::FileRef(mUrl.toLocalFile().toUtf8());
  }

  //! Set the title.
  mTitle = title;

  //! Update metadata.
  //BEGIN
  if (rFile->property(NIE_TITLE).isValid())
    rFile->setProperty(NIE_TITLE, Nepomuk::Variant(mTitle));
  else
    rFile->addProperty(NIE_TITLE, Nepomuk::Variant(mTitle));

  if (rFile->property(NID3_TITLE).isValid())
    rFile->setProperty(NID3_TITLE, Nepomuk::Variant(mTitle));
  else
    rFile->addProperty(NID3_TITLE, Nepomuk::Variant(mTitle));
  id3File->tag()->setTitle(mTitle.toStdString().c_str());
  //END

  if(!mByDemand)
  {
    delete rFile;
    delete id3File;
    rFile = 0x0L;
    id3File = 0x0L;
  }
}

void MediaItem::setUrl(KUrl url)
{
  // TODO
}

void MediaItem::setYear(int year)
{
  if(!mByDemand)
  {
    rFile = new Nepomuk::Resource(mUrl);
    id3File = new TagLib::FileRef(mUrl.toLocalFile().toUtf8());
  }

  //! Set the year.
  mYear = year;

  //! Update metadata.
  //BEGIN
  if (rFile->property(NID3_ORIGINALRELASEYEAR).isValid())
    rFile->setProperty(NID3_ORIGINALRELASEYEAR, Nepomuk::Variant(mYear));
  else
    rFile->addProperty(NID3_ORIGINALRELASEYEAR, Nepomuk::Variant(mYear));

  if (rFile->property(NID3_RECORDINGYEAR).isValid())
    rFile->setProperty(NID3_RECORDINGYEAR, Nepomuk::Variant(mYear));
  else
    rFile->addProperty(NID3_RECORDINGYEAR, Nepomuk::Variant(mYear));
  id3File->tag()->setYear(mYear);
  //END

  if(!mByDemand)
  {
    delete rFile;
    delete id3File;
    rFile = 0x0L;
    id3File = 0x0L;
  }
}

#include "MediaItem.moc"
