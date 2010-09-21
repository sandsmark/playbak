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

#ifndef PLAYBAK_COMPOSEDMEDIAITEMDATA_H
#define PLAYBAK_COMPOSEDMEDIAITEMDATA_H

#include <QString>

class ComposedMediaItemData
{
  private:
    //! The composed media item's composer.
    /**
     * Nepomuk direction:
     *  nid3:composer: http://www.semanticdesktop.org/ontologies/nid3/#composer
     * ID3:
     *  TCOM
     */
    QString mComposer;
  public:
    //! Returns the composed media item's compositor.
    QString compositor();
  public:
    //! Set the composed media item's composer.
    /*!
     * \param composer the compositor's name.
     */
    void setComposer(QString composer);
}

#endif //PLAYBAK_COMPOSEDMEDIAITEMDATA_H
 
