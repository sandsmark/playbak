/*
    The PlaybaK Multimedia Player's library.
    Copyright (C) 2010 PlaybaK Development Team (see AUTHORS file)
    
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef PLAYBAK_SERIEMEDIAITEM_H 
#define PLAYBAK_SERIEMEDIAITEM_H

#include "PublishableMediaItemData.hpp"
#include "VideoMediaItem.hpp"

#include <QMap>
#include <QString>

//! The serie's media item's class.
class SerieMediaItem : public PublishableMediaItemData,
                       public VideoMediaItem
{
  private:
    //! The serie media item's chapter number.
    int     mChapter;
    
    //! The serie media item's chapter name.
    /**
     * ["Language", "Name"]
     */
    /*!
     * NOTE Is not the same as 'MediaItem::mName'?
     */
    QMap<QString,QString> mChapterName;
    
    //! The serie media item's season number.
    int     mSeason;
  public:
    //! Returns the serie media item's chapter number.
    int chapter();
    
    //! Returns the serie media item's chapter name.
    QMap<QString,QString> chapterName();
    
    //! Returns the serie media item's season number.
    int season();
  public:
    //! Returns the serie media item's chapter number.
    /*!
     * \param chapter the serie's chapter number.
     */
    void setChapter(int chapter);
    
    //! Returns the serie media item's chapter name.
    /*!
     * \param chapterName the serie's chapter's name.
     */
    void setChapterName(QMap<Qstring,QDate> chapterName);
    
    //! Returns the serie media item's season number.
    /*!
     * \param season the serie's season number.
     */
    void setSeason(int season);
};

#endif //PLAYBAK_SERIEMEDIAITEM_H
