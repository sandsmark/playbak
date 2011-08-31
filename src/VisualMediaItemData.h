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

#ifndef PLAYBAK_VISUALMEDIAITEMDATA_H
#define PLAYBAK_VISUALMEDIAITEMDATA_H

#include <KDE/KUrl>

//! The visual media item's class.
class VisualMediaItemData
{
  public:
    VisualMediaItemData(KUrl file);
  private:
    //! The visual media item's brightness.
    /**
     * nexif:brightnessValue (range [-99.99; 99.99]): http://www.semanticdesktop.org/ontologies/2007/05/10/nexif/#brightnessValue
     */
    int mBrightness;
    
    //! The visual media item's contrast.
    /**
     * Nepomuk direction:
     *  nexif:contrast: http://www.semanticdesktop.org/ontologies/2007/05/10/nexif/#contrast
     */
    int mContrast;
    
    //! The visual media item's height.
    /**
     * Nepomuk direction:
     *  nexif:height: http://www.semanticdesktop.org/ontologies/2007/05/10/nexif/#height
     */
    int mHeight;
    
    //! The visual media item's hue.
    /**
     * Nepomuk have not.
     */
    int mHue;
    
    //! The visual media item's saturation.
    /**
     * Nepomuk direction:
     *  nexif.saturation: http://www.semanticdesktop.org/ontologies/2007/05/10/nexif/#saturation
     */
    int mSaturation;
    
    //! The visual media item's width.
    /**
     * Nepomuk direction:
     *  nexif:width: http://www.semanticdesktop.org/ontologies/2007/05/10/nexif/#width
     */
    int mWidth;
  public:
    //! Returns the visual media item's brightness.
    int brightness();
    
    //! Returns the visual media item's contrast.
    int contrast();
    
    //! Returns the visual media item's height.
    int height();
    
    //! Returns the visual media item's hue.
    int hue();
    
    //! Returns the visual media item's saturation.
    int saturation();
    
    //! Returns the visual media item's width.
    int width();
  // NOTE Why returns int?
  public:
    //! Set the visual media item's brightness.
    /*!
     * \param brightness the brightness.
     */
    virtual int setBrightness(int brightness) = 0;
    
    //! Set the visual media item's contrast.
    /*!
     * \param contrast the contrast.
     */
    virtual int setContrast(int contrast) = 0;
    
    //! Set the visual media item's height.
    /*!
     * \param height the height.
     */
    virtual int setHeight(int height) = 0;
    
    //! Set the visual media item's hue.
    /*!
     * \param hue the hue.
     */
    virtual int setHue(int hue) = 0;
    
    //! Set the visual media item's saturation.
    /*!
     * \param saturation the saturation.
     */
    virtual int setSaturation(int saturation) = 0;
    
    //! Set the visual media item's width.
    /*!
     * \param width the width.
     */
    virtual int setWidth(int width) = 0;
};

#endif //PLAYBAK_VISUALMEDIAITEMDATA_H
