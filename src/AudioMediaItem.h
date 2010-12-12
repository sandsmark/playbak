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

#ifndef PLAYBAK_AUDIOMEDIAITEM_H
#define PLAYBAK_AUDIOMEDIAITEM_H

#include <QObject>
#include <QString>

#include <KDE/KUrl>

#include <AlbumMediaItemData.h>
#include <ArtisticalMediaItemData.h>
#include <ComposedMediaItemData.h>
#include <MediaItem.h>
#include <PlayableMediaItemData.h>

//! The audio media item's class.
//NOTE: IMPORTANT: The order is important MediaItem need be first because have the QObject hineritance
// see http://slopjong.de/2008/10/07/staticmetaobject-is-not-a-member/
class AudioMediaItem : public MediaItem,
                       public PlayableMediaItemData,
                       public AlbumMediaItemData,
                       public ArtisticalMediaItemData,
                       public ComposedMediaItemData
{
  Q_OBJECT
  public:
    struct Subtype{
      //! The audio media item's subtypes.
      enum AudioMediaItemSubtype{
        NORMAL = 0,   /*!< Normal audio. */
        INSTRUMENTAL, /*!< Instrumental audio. */
        REMIX,        /*!< Remix audio. */
        VOICE         /*!< Voice audio. */
      };
    };

    //! The audio media item's contructor from MediaItem.
    /*!
     * \param url the media source url.
     */
    explicit AudioMediaItem(const MediaItem& copy_mediaitem);
    
    //! The audio media item's copy contructor.
    /*!
     * \param url the media source url.
     */
    explicit AudioMediaItem(const AudioMediaItem& copy);
    
    //! The audio media item's contructor.
    /*!
     * \param url the media source url.
     */
    AudioMediaItem(KUrl url, bool byDemand = false);
  private:     
    //! The audio media item's subtype.
    Subtype::AudioMediaItemSubtype mSubtype;
signals:
  void constructAudioMediaItem();
private:
  class AudioMediaItemConstructor : public QThread {
  public:
    AudioMediaItemConstructor(AudioMediaItem* p) {
      parent = p;
    }
    AudioMediaItem* parent;
    
    void run() {
      parent->firstConstructAudioMediaItem();
    }
  };
  friend class AudioMediaItemConstructor;
private slots:
  void firstConstructAudioMediaItem();
public:
  //! Returns the playable media item's duration time.
  virtual QTime   duration();
  
  //! Returns the playable media item's genre.
  virtual QString genre();
  
  //! Returns the playable media item's involved persons.
  virtual QStringList involvedPersons();
  
  //! Returns the playable media item's language.
  virtual QString language();

  //! Returns the album media item's album's name.
  QString album();
  
  //! Returns the album media item's track number.
  int     trackNumber();

  //! Returns the composed media item's composer.
  QString composer();
protected slots:
  virtual void loadAudioMediaItemMetadata();
  public:
    //! Returns the audio media item's subtype.
    Subtype::AudioMediaItemSubtype subtype();
 public:
    //! Set the artistical media item's website.
    /*!
     * Need be overloaded because the file name is in MediaItem
     * \param url the artist's website url.
     */
    virtual void setArtistWebsite(KUrl url){};
    
    //! Set the artistical media item's original version.
    /**
     * Need be overloaded because the file name is in MediaItem
     */
    virtual void setOriginalMedia(int linkId){};
    
    //! Set the composed media item's composer.
    /*!
     * Need be overloaded because the file name is in MediaItem
     * \param composer the compositor's name.
     */
    virtual void setComposer(QString composer) {};

    //! Set the album media item's album's name.
    /*!
     * Need be overloaded because the file name is in MediaItem
     * \param album the album's name.
     */
    virtual void setAlbum(QString album) {};
    
    //! Set the album media item's track number.
    /*!
     * Need be overloaded because the file name is in MediaItem
     * \param trackNumber the audio's track number.
     */
    virtual void setTrackNumber(int trackNumber) {};
  public:
    //! Set the audio media item's subtype.
    /*!
     * \param subtype the audio's subtype.
     */
    void setSubtype(Subtype::AudioMediaItemSubtype subtype);
};

#endif //PLAYBAK_AUDIOMEDIAITEM_H
