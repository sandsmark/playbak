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

#ifndef PLAYBAK_MEDIAITEM_H
#define PLAYBAK_MEDIAITEM_H

#include <taglib/fileref.h>
#include <taglib/tag.h>

#include <QDate>
#include <QFileSystemWatcher>
#include <QMap>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QThread>

#include <Nepomuk/Resource>
#include <Phonon/MediaObject>

#include <KDE/KUrl>

#include <CollectionItem.h>

//! The media item's class.
class MediaItem : public CollectionItem
{
  Q_OBJECT
  public:
    struct Type{
      //! The media item's types.
      enum MediaItemType{
        INVALID = 0,
        AUDIO, /*!< Audio medias. */
        IMAGE,     /*!< Image medias. */
        VIDEO      /*!< Video medias. */
      };
    };
    //! The media item's copy contructor.
    /*!
     * \param copy the media item to copy.
     */
    explicit MediaItem(const MediaItem& copy);
    
    //! The media item's contructor.
    /*!
     * \param url the media item source url.
     */
    MediaItem(KUrl url, bool byDemand = false);
    virtual ~MediaItem()
    {
    }
signals:
  void constructMediaItem();
private:
private slots:
  void firstConstructMediaItem();
  protected:
    //BEGIN Created to optimize the construction
    bool mByDemand;
    Nepomuk::Resource *rFile;
    Nepomuk::Variant *variant;
    TagLib::FileRef *id3File;
    //END
    //! The media item's artist's name.
    /** Nepomuk direction:
     * Audio: 
     *    Leader artist: http://www.semanticdesktop.org/ontologies/nid3/#leadArtist
     *    Original artist: http://www.semanticdesktop.org/ontologies/nid3/#originalArtist
     * Video: Have not, we need use the audio autor (in Nepomuk a vidio is a subclass of audio)
     * Image:
     *    Photo artist: http://www.semanticdesktop.org/ontologies/2007/05/10/nexif/#artist
     *    Element creator: http://www.semanticdesktop.org/ontologies/2007/03/22/nco#creator
     *    nexif:artist; http://www.semanticdesktop.org/ontologies/2007/05/10/nexif/#artist
     */
    QString mArtist;
    
    //! An url to Copyright information, may be a web url or a local location.
    /** Nepomuk direction:
     * Have not, but have:
     * Copyright (all the copyright): http://www.semanticdesktop.org/ontologies/2007/01/19/nie/#copyright
     * Licence (all the licence): http://www.semanticdesktop.org/ontologies/2007/01/19/nie/#license
     * Licence type (GLP, BSD, ect): http://www.semanticdesktop.org/ontologies/2007/01/19/nie/#licenseType
     */
    KUrl    mCopyrightInformationURL;
    
    //! The media item's creation date.
    /** Nepomuk direction:
     * Element created at: http://www.semanticdesktop.org/ontologies/2007/01/19/nie/#contentCreated
     * File created: http://www.semanticdesktop.org/ontologies/2007/03/22/nfo/#fileCreated
     */
    QDate   mCreationDate;
    
    //! The media item's file size expressed in bytes.
    qint64  mFileSize;
    
    //! The media item's ID.
    /*!
     * NOTE: May exist?
     * This is the same as the mArtist var. We use only Nepomuk, and because nepomuk not uses ID, we don't.
     * We think this is not necessary.
     */
    int     mId;
    
    //! A list of the media item's keywords.
    /** Nepomuk direction:
     * Element keyword: http://www.semanticdesktop.org/ontologies/2007/01/19/nie/#keyword
     */
    QStringList mKeywords;
    
    //! The media item's last update date.
    /** Nepomuk direction:
     * Element last modified: http://www.semanticdesktop.org/ontologies/2007/01/19/nie/#contentLastModified
     * File last modified: http://www.semanticdesktop.org/ontologies/2007/03/22/nfo/#fileLastModified
     */
    QDate   mLastUpdate;
    
    //! The media item's license.
    /** Nepomuk direction:
     * Licence (all the licence): http://www.semanticdesktop.org/ontologies/2007/01/19/nie/#license
     */
    QString mLicense;
    
    //! The media item's MIME type.
    /** Nepomuk direction:
     * Element mime type: http://www.semanticdesktop.org/ontologies/2007/01/19/nie/#mimeType
     */
    QString mMimetype;
    
    //! The media item's rating.
    /** Nepomuk direction:
     * nao:rating [range [0,10] float, 0 means is not set): http://www.semanticdesktop.org/ontologies/nao/#rating
     */
    double   mRating;
    
    //! The media item's score.
    /** Nepomuk direction:
     * nao:score (range [0,1] float): http://www.semanticdesktop.org/ontologies/nao/#score
     */
    double     mScore;
    
    //! The similars artists.
    /** Nepomuk direction:
     * Have not
     */
    QMap<QString,int> mSimilarArtists;
    
    //! The similars media items.
    /** Nepomuk direction:
     * Have not
     */
    QMap<QString,int> mSimilarMedias;
    
    //! A list of the media item's tags.
    /*!
     * NOTE Is not the same as mKeywords? If it's remove ones.
     * Nepomuk uses tags, no keywords. Anyway, we can use both values, but, what's the difference within tags and keywords?
     */
    /** 
     * Nepomuk direction:
     * nao:tag: http://semanticdesktop.org/ontologies/2007/08/15/nao#Tag
     */
    QStringList mTags;
    
    //! The media item's title.
    /**
     * Neopomuk direction:
     * nie:title: http://www.semanticdesktop.org/ontologies/nie/#title
     * nid3: http://www.semanticdesktop.org/ontologies/nid3/#title
     */
    QString mTitle;

    //! The media item's source url.
    /**
     * Nepomuk direction:
     * nie:url: http://www.semanticdesktop.org/ontologies/2007/01/19/nie#url
     */
    KUrl    mUrl;
    
    //! The media item's year.
    /*!
     * NOTE Is not the same as mCreationDate? If it's remove mCreationDate.
     * No, because a image and a movie has Year too. e.g. for Wall-e's movie this may be '2008'. But we think this is the same as mCreationDate.
     */
    /**
     * Nepomuk direction:
     * nid3:originalReleaseYear: http://www.semanticdesktop.org/ontologies/nid3/#originalReleaseYear
     * nid3:recordingYear: http://www.semanticdesktop.org/ontologies/nid3/#recordingYear
     */
    int     mYear;
  public:
    //! Returns the media item's artist's name.
    QString artist();
    
    //! Returns the media item's copyright information url.
    KUrl    copyrightInformationURL();
    
    //! Returns the media item's creation date.
    QDate   creationDate();
    
    //! Returns the media item's file size expressed in bytes.
    qint64  fileSize();
    
    //! Returns the media item's ID.
    int     id();
    
    //! Returns the media item's keywords.
    QStringList keywords();
    
    //! Returns the media item's last update.
    QDate   lastUpdate();
    
    //! Returns the media item's license.
    /*!
     * For example:
     * GPLv3
     * Creative Common Atributtion - Share Alike
     * 
     * Only the license's name, not the full license text.
     */
    QString license();
    
    //! Returns the media item's mimetype.
    /*!
     * For example:
     * audio/ogg
     */
    QString mimetype();
    
    //! Returns the media item's score.
    /*!
     * A value in the range [0-100].
     * This takes into account the complete play times, and the
     * skip times.
     */
    double     score();
    
    //! Returns the media item's rating.
    /*!
     * A value in the range [0-10].
     * NOTE Is it's then may be as you say :)
     */
    double    rating();
    
    //! Returns the similars artist.
    /*!
     * The map's key is associate with a percentage that indicate the
     * percentage similarity: ["Artist","Percentage"].
     */
    QMap<QString,int> similarsArtists();
    
    //! Returns the similars media items.
    /*!
     * The map's key is associate with a percentage that indicate the
     * percentage similarity: ["MediaItem","Percentage"].
     */
    QMap<QString,int> similarsMedias();
    
    //! Returns the media item's tags.
    QStringList tags();
    
    //! Returns the media item's title.
    QString title();
    
    //! Returns the media item's url.
    KUrl    url() const;
    
    //! Returns the media item's year.
    int     year();
  signals:
    void metadataChanged();
  protected slots:
    virtual void loadMediaItemMetadata();
  public:
    //! Returns true if has the keyword, else false.
    /*!
     * \param keyword the keyword.
     */
    bool hasKeyword(QString keyword);
    
    //! Returns true if has the artist's name in the similars' artists list, else false.
    /*!
     * \param artistName the similar's artist's name.
     */
    bool hasSimilarArtist(QString artistName);
    
    //! Returns true if has the media item's name in the similars' medias list, else false.
    /*!
     * \param mediaName the similar's media item's name.
     */
    bool hasSimilarMedia(QString mediaName);
  public:
    //! Add a keyword to media item.
    /*!
     * \param keyword the keyword.
     */
    void addKeyword(QString keyword);
    
    //! Remove a keyword from media item.
    /*!
     * \param keyword the keyword.
     */
    void removeKeyword(QString keyword);
    
    //! Add a similar artist's name to media item.
    /*!
     * The map's key is associate with a percentage that indicate the
     * percentage similarity: ["Artist","Percentage"].
     */
    /*!
     * \param artistName the similar's key.
     * \param percentage the similarity percentage.
     */
    void addSimilarArtist(QString artistName, int percentage);
    
    //! Add a similar media item's name to media item.
    /*!
     * The map's key is associate with a percentage that indicate the
     * percentage similarity: ["MediaItem","Percentage"].
     */
    /*!
     * \param mediaName the similar's key.
     * \param percentage the similarity percentage.
     */
    void addSimilarMedia(QString mediaName, int percentage);
    
    //! Remove a similar artist's name from the media item.
    /*!
     * \param artistName the similar's key.
     */
    void removeSimilarArtist(QString artistName);
    
    //! Remove a similar media item's name from the media item.
    /*!
     * \param mediaName the similar's key.
     */
    void removeSimilarMedia(QString mediaName);
    
    //! Add a keyword to media item.
    /*!
     * \param tag the tag.
     */
    void addTag(QString tag);
  public:
    //! Set the media item's artist.
    /*!
     * \param artist the artist name.
     */
    void setArtist(QString artist);
    
    //! Set the media item's copyright information url.
    /*!
     * \param url the copyright's information url.
     */
    void setCopyrightInformationURL(KUrl url);
    
    //! Set the media item's creation date.
    /*!
     * \param creationDate the creation date.
     */
    void setCreationDate(QDate creationDate);
    
    //! Set the media item's ID.
    /*!
     * \param id the id.
     */
    void setId(int id);
    
    //! Set the media item's keywords.
    /*!
     * \param keywords the keywords.
     */
    void setKeywords(QStringList keywords);
    
    //! Set the media item's last update.
    /*!
     * \param lastUpdate the last update date.
     */
    void setLastUpdate(QDate lastUpdate);
    
    //! Set the media item's license.
    /*!
     * For example:
     * GPLv3
     * Creative Common Atributtion - Share Alike
     * 
     * Only the license's name, not the full license text.
     */
    /*!
     * \param license the license.
     */
    void setLicense(QString license);
    
    //! Set the media item's mimetype.
    /*!
     * For example:
     * audio/ogg
     */
    /*!
     * \param mimetype the mimetype.
     */
    void setMimetype(QString mimetype);
    
    //! Set the media item's score.
    /*!
     * A value in the range [0-100].
     * This takes into account the complete paly times, and the
     * skip times.
     */
    /*!
     * \param score the score.
     */
    void setScore(double score);
    
    //! Set the media item's rating.
    /*!
     * A value in the range [0-5].
     * Note only values as 1.0, 3.5 are valid. This is the decimal part
     * may be 0 or 5 only.
     */
    /*!
     * \param rating the rating.
     */
    void setRating(double rating);
    
    //! Set the similars media items.
    /*!
     * The map's key is associate with a percentage that indicate the
     * percentage similarity: ["Artist","Percentage"].
     */
    /*!
     * \param similarArtist the similars artists.
     */
    void setSimilarArtists(QMap<QString,int> similarArtist);
    
    //! Set the similars artists.
    /*!
     * The map's key is associate with a percentage that indicate the
     * percentage similarity: ["MediaItem","Percentage"].
     */
    /*!
     * \param similarMedias the similars media items.
     */
    void setSimilarMedias(QMap<QString,int> similarMedias);
    
    //! Set the media item's tags.
    /*!
     * \param tags the tags.
     */
    void setTags(QStringList tags);
    
    //! Set the media item's artist title.
    /*!
     * \param title the title.
     */
    void setTitle(int title);

    //! Set the media item's source url.
    /*!
     * \param url the source url.
     */
    void setUrl(KUrl url);
    
    //! Set the media item's year.
    /*!
     * \param year the year.
     */
    void setYear(int year);
};

#endif //PLAYBAK_MEDIAITEM_H
