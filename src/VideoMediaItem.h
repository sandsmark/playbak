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

#ifndef PLAYBAK_VIDEOMEDIAITEM_H
#define PLAYBAK_VIDEOMEDIAITEM_H

#include <QString>

#include <MediaItem.h>
#include <PlayableMediaItemData.h>
#include <VisualMediaItemData.h>

#include <KDE/KUrl>

//! The video media item's class.
class VideoMediaItem : public PlayableMediaItemData,
                       public VisualMediaItemData,
                       public MediaItem
{
  public:
    struct Subtype{
      //! The video media item's types.
      enum VideoMediaItemtype{
        PERSONAL = 0,      /*!< Personal video. */
        VIDEOCLIP,         /*!< Videoclip. */
        MOVIES,            /*!< Movie video. */
        SERIES,            /*!< Serie video. */
        INSTRUMENTALMUSIC, /*!< Instrumental music video. */
        REMIXMUSIC         /*!< Remix music video. */
      };
    };
    VideoMediaItem(KUrl url, bool byDemand = false);

    VideoMediaItem(const MediaItem& copy_mediaitem);

    VideoMediaItem(const VideoMediaItem& copy);
  protected slots:
    virtual void loadVideoMediaItemMetadata();
  private:  
    //! The video media item's editor.
    /**
     * Nepomuk have not.
     * ID3 have not.
     */
    QString mEditor;
    
    //! The video media item's producer.
    /**
     * Nepomuk have not.
     * ID3 have not.
     */
    QString mProducer;
    
    //! The video media item's subtype.
    Subtype::VideoMediaItemtype mSubtype;
    
    //! The video media item's tagline.
    /**
     * Nepomuk have not.
     * ID3 have not.
     */
    QString mTagline;
  public:
    //! Returns the video media item's editor.
    QString editor();
    
    //! Returns the video media item's producer.
    QString producer();
    
    //! Returns the video media item's subtype.
    Subtype::VideoMediaItemtype subtype();
    
    //! Returns the video media item's tagline.
    QString tagline();
  //! Abstracts in VisualMediaItemData.
  public:
    //! Set the visual media item's brightness.
    /*!
     * \param brightness the brightness.
     */
    virtual int setBrightness(int brightness) {return 0;};

    //! Set the visual media item's contrast.
    /*!
     * \param contrast the contrast.
     */
    virtual int setContrast(int contrast) {return 0;};

    //! Set the visual media item's height.
    /*!
     * \param height the height.
     */
    virtual int setHeight(int height) {return 0;};

    //! Set the visual media item's hue.
    /*!
     * \param hue the hue.
     */
    virtual int setHue(int hue) {return 0;};

    //! Set the visual media item's saturation.
    /*!
     * \param saturation the saturation.
     */
    virtual int setSaturation(int saturation) {return 0;};

    //! Set the visual media item's width.
    /*!
     * \param width the width.
     */
    virtual int setWidth(int width) {return 0;};
  public:
    //! Set the video media item's editor.
    /*!
     * NOTE May need to be in PlayableMediaItemData
     */
    /*!
     * \param editor the video's editor's name.
     */
    void setEditor(QString editor);
    
    //! Set the video media item's productor.
    /*!
     * NOTE May need to be in PlayableMediaItemData
     */
    /*!
     * \param producer the video's producer's name.
     */
    void setProducer(QString producer);
    
    //! Set the video media item's subtype.
    /*!
     * \param subtype the video's subtype.
     */
    void setSubtype(Subtype::VideoMediaItemtype subtype);
    
    //! Set the video media item's tagline.
    /*!
     * \param tagline the video's tagline.
     */
    void setTagline(QString tagline);
};

#endif //PLAYBAK_VIDEOMEDIAITEM_H
