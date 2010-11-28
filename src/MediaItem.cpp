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

#include <Nepomuk/Resource>
#include <Nepomuk/ResourceManager>
#include <Nepomuk/Tag>
#include <Nepomuk/Types/Class>
#include <Nepomuk/Variant>

#include <Phonon/MediaObject>

#include <MediaItem.h>
#include <Ontologies.h>

MediaItem::MediaItem(KUrl url) :
  mUrl(url),
  CollectionItem(CollectionItem::Type::MIX) // TODO: Temporal el MIX
{
  // First we load the metadata
  loadMetadata(url.toLocalFile());
//   try
//   {
    mFileWatcher = 0x0L; // If 'new' fail, will be null
    mFileWatcher = new QFileSystemWatcher(this);
//   }
//   catch(..)
//   {
    // Put in null to not delete the pointer in the destructor
//     mFileWatcher = 0x0L;
//   }
  // After that (because if is before an the file is changed while is load the metadata, can be mistakenly loaded)
  // we observ the file to see any change, if change, we re-read the metadata.
  mFileWatcher->addPath(url.toLocalFile());
  connect(mFileWatcher,SIGNAL(fileChanged(QString)),this,SLOT(loadMetadata(QString)));
}
void MediaItem::loadMetadata(QString url)
{
  // TODO: Verifi if is a valid media (image, video or music)
  //       if is not: throw
  Nepomuk::Resource rFile(url);
  Nepomuk::Variant variant;
  TagLib::FileRef id3File(url.toStdString().c_str());

  // We verity is Nepomuk was initialized (is recomended if we use thread, and we use it)
  if (rFile.manager()->initialized())
    rFile.manager()->init();
  // Not readed
  //   mCopyrightInformationURL
  // Read the datas in parallel
//   #pragma omp parallel sections
  {
//     #pragma omp section
    {
      if ( (variant = rFile.property(NAO_CREATED)).isValid() )
        mCreationDate = variant.toDate();
      else if ( (variant = rFile.property(NFO_FILECREATED)).isValid() )
        mCreationDate = variant.toDate();
      else if ( (variant = rFile.property(NIE_CONTENTCREATED)).isValid() )
        mCreationDate = variant.toDate();
      else
        mCreationDate = QDate();

    }
    
//     #pragma omp section
    {
      if ( (variant = rFile.property(NIE_KEYWORD)).isValid() )
        mKeywords = variant.toStringList();
      else
        mKeywords = QStringList();
    }
    
//     #pragma omp section
    {
      if ( (variant = rFile.property(NFO_LASTUPDATED)).isValid() )
        mLastUpdate = variant.toDate();
      else if ( (variant = rFile.property(NIE_LASTUPDATE)).isValid() )
        mLastUpdate = variant.toDate();
      else
        mLastUpdate = QDate();
    }
    
//     #pragma omp section
    {
      if ( (variant = rFile.property(NIE_LICENSETYPE)).isValid() )
        mLicense = variant.toString();
      else
        mLicense = QString();
    }
    
//     #pragma omp section
    {
      if ( !(variant = rFile.property(NIE_MIMETYPE)).toString().isEmpty() )
      {
//           qDebug("Detectado, es:");
        mMimetype = variant.toString();
      }
      // If have not mimetype, we set manualy the mime type, because is necesary
      else
      {
//           qDebug("No Detectado");
        // Load the media widht Phonon to try to detect the type
        Phonon::MediaObject *media = new Phonon::MediaObject();
        media->setCurrentSource(Phonon::MediaSource(url));
        if (media->isValid())
        {
          // We wait to finish to read
          QEventLoop loop;
          QObject::connect(media, SIGNAL(stateChanged(Phonon::State,Phonon::State)), &loop, SLOT(quit()));
          loop.exec();
          
          // If is an video
          if (media->hasVideo())
            setMimetype("video/"); // TODO: load the full mimetype
          // Else is an audio
          else
            setMimetype("audio/"); // TODO: load the full mimetype
        }
        //We try to load like an image
        else 
        {
          QImage img;
          img.load(url);
          // If is an image
          if (!img.isNull())
            setMimetype("image/"); // TODO: load the full mimetype
        }
        delete media;
      }
      
//       QHash<QUrl, Nepomuk::Variant> properties = rFile.properties();
//       QHashIterator<QUrl, Nepomuk::Variant> it( properties );
//       while( it.hasNext() ) {
//         it.next();
//         //       qDebug(Nepomuk::Types::Property( it.key() ).label())
//         //       kdDebug() << Nepomuk::Types::Property( it.key() ).label() << ": " << it.value().toString() << endl;
//         kdDebug() << it.key() << ": " << it.value().toString() << endl;
//       }
//       if (rFile.property("http://www.semanticdesktop.org/ontologies/2007/01/19/nie#mimeType").isValid() )
//       qDebug("Es valido");
    }
    
//     #pragma omp section
    {
      if ( (variant = rFile.property(NAO_SCORE)).isValid() )
        mScore = variant.toDouble();
      else
        mScore = 0.0;
    }
    
//     #pragma omp section
    {
      if ( (variant = rFile.property(XESAM_RATING)).isValid() )
        mRating = variant.toDouble();
      else if ( (variant = rFile.property(XESAM_AUTORATING)).isValid() )
        mRating = variant.toDouble();
      else
        mRating = 0.0;
    }
    
//     #pragma omp section
    {
      if ( (variant = rFile.property(NAO_TAG)).isValid() )
        mTags = variant.toStringList();
      else
        mTags = QStringList();
    }
    
    // Search the correct title
    // First we search in the normal title
    // if is not, we use the id3 title (is no problem if is empty, because we have no more
    // sites to search )
//     #pragma omp section
    {
      if ( (variant = rFile.property(NID3_TITLE)).isValid() )
        mTitle = variant.toString();
      else if ( (variant = rFile.property(NIE_TITLE)).isValid() )
        mTitle = variant.toString();
      else if ( (variant = rFile.property(XESAM_TITLE)).isValid() )
        mTitle = variant.toString();
      else
        mTitle = QString();
    }
    // We verificate with ID3 tag
//     #pragma omp section
    {
      if ( !id3File.isNull() && id3File.tag()->title().toCString() != mTitle.toStdString().c_str() )
      {
        // ID3 tag is more importan than data stored in Nepomuk.
        // We use ID3 tag and update the data stored in nepomuk
        mTitle = id3File.tag()->title().toCString();
        rFile.setProperty(NID3_TITLE, Nepomuk::Variant(mTitle) );
        rFile.setProperty(NIE_TITLE, Nepomuk::Variant(mTitle) );
        // We do not save in Xesam because is depercated
      }
    }
    
    // We search the year of the media in 2 sites
    // First we search in the original relase year id3 tag
    // if is not we use the recording year (is no problem if is empty, because we have no more
    // sites to search )
//     #pragma omp section
    {
      if ( (variant = rFile.property(NID3_ORIGINALRELASEYEAR)).isValid() )
        mYear = variant.toInt();
      else if ( (variant = rFile.property(NID3_RECORDINGYEAR)).isValid() )
        mYear = variant.toInt();
      else if ( (variant = rFile.property(XESAM_CONTENTCREATED)).isValid() )
        mYear = variant.toInt();
    }
    
    // We verificate with ID3 tag
//     #pragma omp section
    {
      if ( !id3File.isNull() && id3File.tag()->year() != mYear )
      {
        // ID3 tag is more importan than data stored in Nepomuk.
        // We use ID3 tag and update the data stored in nepomuk
        mYear = id3File.tag()->year();
        rFile.setProperty(NID3_ORIGINALRELASEYEAR, Nepomuk::Variant(mYear) );
        rFile.setProperty(NID3_RECORDINGYEAR, Nepomuk::Variant(mYear) );
        // We do not save in Xesam because is depercated
      }
    }
    
    // We search the audio artist
    // First we search in the lider artist
    // if is not we use the original artist (is no problem if is empty, because we have no more
    // sites to search )
//     #pragma omp section
    {
      if ( (variant = rFile.property(NID3_ORIGINALARTIST)).isValid() )
        mArtist = variant.toString();
      else if ( (variant = rFile.property(NIE_LEADERARTIST)).isValid() )
        mArtist = variant.toString();
      else if ( (variant = rFile.property(NEXIF_ARTIST)).isValid() )
        mArtist = variant.toString();
      else if ( (variant = rFile.property(XESAM_ARTIST)).isValid() )
        mArtist = variant.toString();
    }
  }
  // End parallel load
  // This section require the data loaded
  
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
    if (rFile.property(NID3_ORIGINALARTIST).isValid())
      rFile.setProperty(NID3_ORIGINALARTIST, Nepomuk::Variant(mArtist));
    else
      rFile.addProperty(NID3_ORIGINALARTIST, Nepomuk::Variant(mArtist));

    if (rFile.property(NIE_LEADERARTIST).isValid())
      rFile.setProperty(NIE_LEADERARTIST, Nepomuk::Variant(mArtist));
    else
      rFile.addProperty(NIE_LEADERARTIST, Nepomuk::Variant(mArtist));
    
    id3File.tag()->setArtist(mArtist.toStdString().c_str());
  }
  // If is an image
  else if (mMimetype.contains("image") )
  {
    if (rFile.property(NEXIF_ARTIST).isValid())
      rFile.setProperty(NEXIF_ARTIST, Nepomuk::Variant(mArtist));
    else
      rFile.addProperty(NEXIF_ARTIST, Nepomuk::Variant(mArtist));
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
  if (rFile.property(NFO_FILECREATED).isValid())
    rFile.setProperty(NFO_FILECREATED, Nepomuk::Variant(mCreationDate));
  else
    rFile.addProperty(NFO_FILECREATED, Nepomuk::Variant(mCreationDate));

  if (rFile.property(NIE_CONTENTCREATED).isValid())
    rFile.setProperty(NIE_CONTENTCREATED, Nepomuk::Variant(mCreationDate));
  else
    rFile.addProperty(NIE_CONTENTCREATED, Nepomuk::Variant(mCreationDate));
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
  if (rFile.property(NIE_KEYWORD).isValid())
    rFile.setProperty(NIE_KEYWORD, Nepomuk::Variant(mKeywords));
  else
    rFile.addProperty(NIE_KEYWORD, Nepomuk::Variant(mKeywords));
}

void MediaItem::setLastUpdate(QDate lastUpdate)
{
  // Load the resource
  Nepomuk::Resource rFile(mUrl.toLocalFile().toStdString().c_str());
  mLastUpdate = lastUpdate;
  // Set last update
  if (rFile.property(NFO_LASTUPDATED).isValid())
    rFile.setProperty(NFO_LASTUPDATED, Nepomuk::Variant(mLastUpdate));
  else
    rFile.addProperty(NFO_LASTUPDATED, Nepomuk::Variant(mLastUpdate));

  if (rFile.property(NIE_LASTUPDATE).isValid())
    rFile.setProperty(NIE_LASTUPDATE, Nepomuk::Variant(mLastUpdate));
  else
    rFile.addProperty(NIE_LASTUPDATE, Nepomuk::Variant(mLastUpdate));
}

void MediaItem::setLicense(QString license)
{
  // Load the resource
  Nepomuk::Resource rFile(mUrl.toLocalFile().toStdString().c_str());
  mLicense = license;
  // Set the license
  if (rFile.property(NIE_LICENSETYPE).isValid())
    rFile.setProperty(NIE_LICENSETYPE, Nepomuk::Variant(mLicense));
  else
    rFile.addProperty(NIE_LICENSETYPE, Nepomuk::Variant(mLicense));
}

void MediaItem::setMimetype(QString mimetype)
{
  // Load the resource
  Nepomuk::Resource rFile(mUrl.toLocalFile().toStdString().c_str());
  mMimetype = mimetype;
  if (rFile.property(NIE_MIMETYPE).isValid())
      rFile.setProperty(NIE_MIMETYPE, Nepomuk::Variant(mMimetype));
  else
    // Set the mime type
    rFile.addProperty(NIE_MIMETYPE, Nepomuk::Variant(mMimetype));
}

void MediaItem::setScore(double score)
{
  // Load the resource
  Nepomuk::Resource rFile(mUrl.toLocalFile().toStdString().c_str());
  mScore = score;
  // Set the score
  if (rFile.property(NAO_SCORE).isValid())
    rFile.setProperty(NAO_SCORE, Nepomuk::Variant(mScore));
  else
    rFile.addProperty(NAO_SCORE, Nepomuk::Variant(mScore));
}

void MediaItem::setRating(double rating)
{
  // Load the resource
  Nepomuk::Resource rFile(mUrl.toLocalFile().toStdString().c_str());
  mRating = rating;
  // Set the rating
  if (rFile.property(XESAM_RATING).isValid())
    rFile.setProperty(XESAM_RATING, Nepomuk::Variant(mRating));
  else
    rFile.addProperty(XESAM_RATING, Nepomuk::Variant(mRating));

  if (rFile.property(XESAM_AUTORATING).isValid())
    rFile.setProperty(XESAM_AUTORATING, Nepomuk::Variant(mRating));
  else
    rFile.addProperty(XESAM_AUTORATING, Nepomuk::Variant(mRating));
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
  if (rFile.property(NAO_TAG).isValid())
    rFile.setProperty(NAO_TAG, Nepomuk::Variant(mTags));
  else
    rFile.addProperty(NAO_TAG, Nepomuk::Variant(mTags));
}

void MediaItem::setTitle(int title)
{
  // Load the resource
  Nepomuk::Resource rFile(mUrl.toLocalFile().toStdString().c_str());
  TagLib::FileRef id3File(mUrl.toLocalFile().toStdString().c_str());
  mTitle = title;
  // Set the rating
  if (rFile.property(NIE_TITLE).isValid())
    rFile.setProperty(NIE_TITLE, Nepomuk::Variant(mTitle));
  else
    rFile.addProperty(NIE_TITLE, Nepomuk::Variant(mTitle));

  if (rFile.property(NID3_TITLE).isValid())
    rFile.setProperty(NID3_TITLE, Nepomuk::Variant(mTitle));
  else
    rFile.addProperty(NID3_TITLE, Nepomuk::Variant(mTitle));
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
  if (rFile.property(NID3_ORIGINALRELASEYEAR).isValid())
    rFile.setProperty(NID3_ORIGINALRELASEYEAR, Nepomuk::Variant(mYear));
  else
    rFile.addProperty(NID3_ORIGINALRELASEYEAR, Nepomuk::Variant(mYear));

  if (rFile.property(NID3_RECORDINGYEAR).isValid())
    rFile.setProperty(NID3_RECORDINGYEAR, Nepomuk::Variant(mYear));
  else
    rFile.addProperty(NID3_RECORDINGYEAR, Nepomuk::Variant(mYear));
  id3File.tag()->setYear(mYear);
}

#include "../include/MediaItem.moc"