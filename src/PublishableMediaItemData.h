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

#ifndef PLAYBAK_PUBLISHABLEMEDIAITEMDATA_H
#define PLAYBAK_PUBLISHABLEMEDIAITEMDATA_H

#include <QDate>
#include <QMap>
#include <QString>

//! The publishable media items' class.
/**
 * This is for items that are published in e.g. TV, CD/DVD.
 */
class PublishableMediaItemData
{
  private:
    //! The publishable media item's air date.
    /**
     * ["Country",AirDate]
     * If was a wolrdwide launch, then the map key may be: "World"
     */
    /**
     * Nepomuk have not.
     * ID3 have not.
     */
    QMap<Qstring,QDate> mAirDate;
  public:
    //! Returns the publishable media item's air date.
    /**
     * ["Country",AirDate]
     * If was a wolrdwide launch, then the map key may be: "World"
     */
    QMap<QString,QDate> airDate();
  public:
    //! Returns the publishable media item's air date.
    /**
     * ["Country",AirDate]
     * If was a wolrdwide launch, then the map key may be: "World"
     */
    /*!
     * \param airDate the serie's air date.
     */
    void setAirDate(QMap<QString,QDate> airDate);
};

#endif //PLAYBAK_PUBLISHABLEMEDIAITEMDATA_H