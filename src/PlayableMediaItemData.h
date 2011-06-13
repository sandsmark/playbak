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

#ifndef PLAYBAK_PLAYABLEMEDIAITEMDATA_H
#define PLAYBAK_PLAYABLEMEDIAITEMDATA_H

// #include <QObject>
#include <QString>
#include <QStringList>
#include <QTime>
#include <QVector>

#include <KDE/KUrl>

//! The playable media item's class.
class PlayableMediaItemData
{
  protected:;
    //! The playable media item's equalizer's bands values.
    /**
     * Nepomuk have not.
     * ID3 tag: EQUA (http://www.id3.org/id3v2.3.0)
     */
    QVector<double>  mAudioEq;
    
    //! The playable media item's audio preamplifier's value.
    /**
     * Nepomuk have not
     * ID have not.
     */
    double  mAudioPreamp;
    
    //! The playable media item's duration.
    /**
     * Nepomuk direction:
     *  nid3:lenght (in milliseconds): http://www.semanticdesktop.org/ontologies/nid3/#length
     * ID3:
     *  TLEN (in milliseconds, http://www.id3.org/id3v2.3.0)
     */
    QTime   mDuration;
    
    //! The playable media item's duration time.
    /**
     * Nepomuk direction:
     *  nid3:contentType (is in): http://www.semanticdesktop.org/ontologies/nid3/#contentType
     * ID3:
     *  TCON (writed like "(31)", see genre list: http://www.id3.org/id3v2.3.0#head-129376727ebe5309c1de1888987d070288d7c7e7)
     */
    QString mGenre;
    
    //! The playable media item's involved persons.
    /**
     * Nepomuk direction:
     *  nid3:involvedPersons: http://www.semanticdesktop.org/ontologies/nid3/#involvedPerson
     * ID3:
     *  IPLS
     */
    QStringList mInvolvedPersons;
    
    //! The playable media item's language.
    /*!
     * NOTE May need to be QStringList.
     */
    /**
     * Nepomuk direction:
     *  nie:language: http://www.semanticdesktop.org/ontologies/nie/#language
     *  nid3:language (lyrics language): http://www.semanticdesktop.org/ontologies/2007/05/10/nid3/#language
     * ID3:
     *  TLAN
     */
    QString mLanguage;
    
    //! The playable media item's start position.
    qint64  mStartat;
  public:
    //! Returns the playable media item's equalizer's bands values.
     QVector<double>  audioEq();
    
    //! Returns a specific playable media item's equalizer's band value.
    /*!
     * \param band the equalizer's band number.
     */
     double  audioEq(int band);
    
    //! Returns the playable media item's preamplifier's value.
     double  audioPreamp();
    
    //! Returns the playable media item's duration time.
    virtual QTime   duration();
    
    //! Returns the playable media item's genre.
  //  virtual QString genre() {};
    
    //! Returns the playable media item's involved persons.
  //  virtual QStringList involvedPersons() {};
    
    //! Returns the playable media item's language.
  //  virtual QString language() {};
    
    //! Returns the playable media item's start position.
     qint64  startAt();
  public:
    //! Add an involved person to playable media item.
    /*!
     * \param person a involved person.
     */
     void addInvolvedPerson(QString person);
    
    //! Remove an involved person from playable media item.
    /*!
     * \param person a involved person.
     */
     void removeInvolvedPerson(QString person);
    
    //! Set the playable media item's audio equalizer's bands values.
    /*!
     * \param audioEq the equalizer.
     */
     void setAudioEq(QVector<double> audioEq);
    
    //! Set a specific playable media item's audio equalizer band.
    /*!
     * \param value the value to set.
     * \param band the band number.
     */
     void setAudioEq(double value, int band);
    
    //! Set the playable media item's duration time.
    /*!
     * \param duration the media duration time.
     */
     void setDuration(QTime duration);
    
    //! Set the playable media item's genre.
    /*!
     * \param genre the media genre.
     */
     void setGenre(QString genre);
    
    //! Set the playable media item's involved persons.
    /*!
     * \param involvedPersons the involved persons.
     */
     void setInvolvedPersons(QStringList involvedPersons);
    
    //! Set the playable media item's language.
    /*!
     * \param language the language.
     */
     void setLanguage(QString language);
    
    //! Set the playable media item's start position.
    /*!
     * \param startAt the media's start position.
     */
     void setStartAt(int startAt);
  public:
     PlayableMediaItemData(KUrl file);
};

#endif //PLAYBAK_PLAYABLEMEDIAITEMDATA_H
