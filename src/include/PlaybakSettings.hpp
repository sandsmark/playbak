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

#ifndef PLAYBAK_SETTINGS_H
#define PLAYBAK_SETTINGS_H
#include <QList>
#include <QString>

#include <kdemacros.h>
#include <KConfig>
#include <KConfigGroup>
#include <KWallet/Wallet>

class PlaybakSettings {
  protected:
    /// The audio config group
    KConfigGroup mAudioConfigGroup;

    /// The audio preamplifier
    qreal mAudioPreamp;

    /// The video brightness
    qreal mBrightness;

    /// The configuration
    KConfig mConfigFile;

    /// The video contrast
    qreal mContrast;
    
    /// The database name
    QString mDataBaseName;

    /// The audio equalizer
    QList<qreal> mEqualizer;

    /// The general config group
    KConfigGroup mGeneralConfigGroup;
    
    /// The host of the database
    QString mHost;
    
    qreal mHue;
    /// The language of the aplication.
    /**
     * Used, for example, to show the name of the chapters of the series.
     */
    QString mLanguage;
    
    /// The password of the user
    QString mPassword;
    
    /// The port of the database
    qint32 mPort;
    
    qreal mSaturation;
    /// the user of the database
    
    QString mUser;

    KConfigGroup mVideoConfigGroup;
    
    qreal mVolume;

    /**
     * Used to save the database information
     */
    KWallet::Wallet *mWalletConfig;

    bool mWalletIsOpen;

    bool mWalletReadedSusefully;
  private slots:
    void isWalletOpen(bool ok);
  protected:
    void loadDatabaseConfig();
  public:
    qreal audioPreamp();
    
    qreal brightness();
    
    qreal contrast();
    
    QString dataBaseName();
    
    QList<qreal> equalizer();
    
    QString host();
    
    QString language();
    
    QString password();
    
    qint32 port();
    
    qreal saturation();
    
    QString user();
    
    qreal volume();
  public:
    void setAudioPromp(qreal audioPreamp);
    
    void setBrightness(qreal brightness);
    
    void setContrast(qreal contrast);
    
    void setDataBaseName(QString dataBaseName);
    
    void setEqualizer(QList<qreal> equalizer);
    
    void setHost(QString host);
    
    void setLanguage(QString language);
    
    void setPassword(QString password);
    
    void setPort(qint32 port);
    
    void setUser(QString user);
    
    void setVolume(qreal volume);
  public:
    PlaybakSettings();
};

#endif