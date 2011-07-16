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

#ifndef PLAYBAK_SETTINGS_H
#define PLAYBAK_SETTINGS_H

#include <QList>
#include <QString>

#include <KDE/KConfig>
#include <KDE/KConfigGroup>
#include <KDE/KWallet/Wallet>
#include <kdemacros.h>

class PlaybakSettings {
  protected:
    //! The audio config group
    KConfigGroup mAudioConfigGroup;

    //! The audio preamplifier
    qreal mAudioPreamp;

    //! The video brightness
    qreal mBrightness;

    //! The configuration
    KConfig mConfigFile;

    //! The video contrast
    qreal mContrast;
    
    //! The database name
    QString mDataBaseName;

    //! The audio equalizer
    QList<qreal> mEqualizer;

    //! The general config group
    KConfigGroup mGeneralConfigGroup;
    
    //! The host of the database
    QString mHost;

    //! The image/video hue.
    qreal mHue;
    //! The language of the aplication.
    /*!
     * Used, for example, to show the name of the chapters of the series.
     */
    QString mLanguage;
    
    //! The password of the user
    QString mPassword;
    
    //! The port of the database
    qint32 mPort;

    //! The image/video saturation.
    qreal mSaturation;
    
    //! The user of the database
    QString mUser;

    //! NOTE ?
    KConfigGroup mVideoConfigGroup;

    //! The audio volume.
    qreal mVolume;

    //! The KWallet iterface.
    /*!
     * Used to save the database information.
     */
    KWallet::Wallet *mWalletConfig;

    //! Indicates if the wallet is open.
    bool mWalletIsOpen;

    //! Indicates if the wallet was read successfully.
    bool mWalletReadSuccessfully;
  private:
    //! Open the wallet and load the configuration from database.
    void setWalletOpen(bool ok);
  protected:
    //! Load the configuration from database.
    void loadConfigFromDatabase();
  public:
    //! Get the audio's preamplifier value.
    qreal audioPreamp();

    //! Get the image/video's brightness value.
    qreal brightness();

    //! Get the image/video's contrast value.
    qreal contrast();

    //! Get the database's name.
    QString dataBaseName();

    //! Get the equalizer's values.
    QList<qreal> equalizer();

    //! Get the hostname.
    QString hostname();

    //! Get the language.
    QString language();

    //! Get the database's password.
    QString password();

    //! Get the database's port.
    qint32 port();

    //! Get the image/video saturation value.
    qreal saturation();

    //! Get the database's username.
    QString username();

    //! Get the audio volume's value.
    qreal volume();
  public:
    //! Set the audio's preamplifier.
    /*!
     * \param audioPreamp The audio's preamplifier.
     */
    void setAudioPreamp(qreal audioPreamp);

    //! Set the image/video's brightness.
    /*!
     * \param brightness The image/video's brightness.
     */
    void setBrightness(qreal brightness);

    //! Set the image/video's contrast.
    /*!
     * \param contrast The image/video's contrast.
     */
    void setContrast(qreal contrast);

    //! Set the database's name.
    /*!
     * \param dataBaseName The database's name.
     */
    void setDataBaseName(QString dataBaseName);

    //! Set the audio's equalizer.
    /*!
     * \param equalizer The audio equalizer.
     */
    void setEqualizer(QList<qreal> equalizer);

    //! Set the database's hostname.
    /*!
     * \param hostname The database's hostname.
     */
    void setHostname(QString hostname);

    //! Set language's value.
    /*!
     * \param language The language's value.
     */
    void setLanguage(QString language);

    //! Set the database's password.
    /*!
     * \param password The database's password.
     */
    void setPassword(QString password);

    //! Set the database's port.
    /*!
     * \param port The database's port.
     */
    void setPort(qint32 port);

    //! Set the database's username.
    /*!
     * \param username The database's username.
     */
    void setUsername(QString username);

    //! Set the audio's volume.
    /*!
     * \param volume The audio's volume.
     */
    void setVolume(qreal volume);
  public:
    PlaybakSettings();
};

#endif