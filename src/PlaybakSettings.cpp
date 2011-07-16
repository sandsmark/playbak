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

#include <QEventLoop>
#include <QByteArray>
#include <QMap>
#include <QVariant>

#include <PlaybakSettings.h>

PlaybakSettings::PlaybakSettings() :
  mConfigFile(QString("PlaybaK"))
{
  mAudioConfigGroup = mConfigFile.group("Audio");
  mVideoConfigGroup = mConfigFile.group("Audio");
  mGeneralConfigGroup = mConfigFile.group("General");
  mWalletReadSuccessfully = false;
//   QObject::connect(mWalletConfig, SIGNAL(walletOpened(bool)),this, SLOT(isWalletOpen(bool)));
  QEventLoop loop;
  QObject::connect(mWalletConfig,SIGNAL(walletOpened(bool)),&loop,SLOT(quit()));
  loop.exec();
  setWalletOpen(true);
  mWalletConfig = KWallet::Wallet::openWallet(KWallet::Wallet::NetworkWallet(),
                                              0,
                                              KWallet::Wallet::Asynchronous);

  mAudioPreamp = QVariant(mAudioConfigGroup.readEntry( "Preamplifier", qreal(0.5) )).toReal();
  mBrightness = QVariant(mVideoConfigGroup.readEntry( "Brightness", qreal(0.5) )).toReal();
  mContrast = QVariant(mVideoConfigGroup.readEntry( "Contrast", qreal(0.5) )).toReal();
  // TODO: Read the equalizer
  mHue = QVariant(mVideoConfigGroup.readEntry( "Hue", qreal(0.5) )).toReal();
  // TODO: Read the language of the sistem to default, not en.
  mLanguage = QVariant(mGeneralConfigGroup.readEntry( "Language", QString("en") )).toString();
  mSaturation = QVariant(mVideoConfigGroup.readEntry( "Saturation", qreal(0.5) )).toReal();
  mVolume = QVariant(mVideoConfigGroup.readEntry( "Volume", qreal(0.5) )).toReal();                                                
}

void PlaybakSettings::setWalletOpen(bool ok)
{
  mWalletIsOpen = ok;
  if (ok)
    loadConfigFromDatabase();
}

void PlaybakSettings::loadConfigFromDatabase()
{
  if (!mWalletConfig->hasFolder("PlaybaK"))
    mWalletConfig->createFolder("PlaybaK");
  mWalletConfig->setFolder("PlaybaK");
  QMap<QString, QString> configMap;
  QByteArray data;
  if (mWalletConfig->hasEntry("DataBase"))
  {
    mWalletConfig->readEntry("DataBase", data);
    mDataBaseName = data;
  }
  if (mWalletConfig->hasEntry("Host"))
  {
    mWalletConfig->readEntry("Host", data);
    mHost = data;
  }
  if (mWalletConfig->hasEntry("User"))
  {
    mWalletConfig->readEntry("User", data);
    mUser = data;
  }
  if (mWalletConfig->hasEntry("Password"))
  {
    mWalletConfig->readEntry("Password", data);
    mPassword = data;
  }
  if (mWalletConfig->hasEntry("Port"))
  {
    mWalletConfig->readEntry("Port", data);
    mPort = QVariant(data).toInt();
  }
  mWalletReadSuccessfully = true;
  
}

qreal PlaybakSettings::brightness()
{
  return mBrightness;
}

qreal PlaybakSettings::contrast()
{
  return mContrast;
}

qreal PlaybakSettings::saturation()
{
  return mSaturation;
}

QList<qreal> PlaybakSettings::equalizer()
{
  return mEqualizer;
}

qreal PlaybakSettings::volume()
{
  return mVolume;
}

qreal PlaybakSettings::audioPreamp()
{
  return mAudioPreamp;
}

QString PlaybakSettings::language()
{
  return mLanguage;
}

QString PlaybakSettings::dataBaseName()
{
  return mDataBaseName;
}

QString PlaybakSettings::hostname()
{
  return mHost;
}

QString PlaybakSettings::username()
{
  return mUser;
}

QString PlaybakSettings::password()
{
  return mPassword;
}

qint32 PlaybakSettings::port()
{
  return mPort;
}

void PlaybakSettings::setBrightness(qreal brightness)
{
  mBrightness = brightness;
  mVideoConfigGroup.writeEntry("Brightness",brightness);
}

void PlaybakSettings::setContrast(qreal contrast)
{
  mContrast = contrast;
  mVideoConfigGroup.writeEntry("Contrast",contrast);
}

void PlaybakSettings::setEqualizer(QList<qreal> equalizer)
{
  // TODO: Create :P
}

void PlaybakSettings::setVolume(qreal volume)
{
  mVolume = volume;
  mAudioConfigGroup.writeEntry("Volume",volume);
}

void PlaybakSettings::setAudioPreamp(qreal audioPreamp)
{
  mAudioPreamp = audioPreamp;
  mAudioConfigGroup.writeEntry("Preamplifier",audioPreamp);
}

void PlaybakSettings::setLanguage(QString language)
{
  mLanguage = language;
  mGeneralConfigGroup.writeEntry("Language",language);
}

void PlaybakSettings::setDataBaseName(QString dataBaseName)
{
  mDataBaseName = dataBaseName;
  if (mWalletIsOpen)
    mWalletConfig->writeEntry("DataBase",dataBaseName.toUtf8());
}

void PlaybakSettings::setHostname(QString hostname)
{
  mHost = hostname;
  if (mWalletIsOpen)
    mWalletConfig->writeEntry("Host", hostname.toUtf8());
}

void PlaybakSettings::setUsername(QString username)
{
  mUser = username;
  if (mWalletIsOpen)
    mWalletConfig->writeEntry("User", username.toUtf8());
}

void PlaybakSettings::setPassword(QString password)
{
  mPassword = password;
  if (mWalletIsOpen)
    mWalletConfig->writeEntry("Password", password.toUtf8());
}

void PlaybakSettings::setPort(qint32 port)
{
  mPassword = port;
  if (mWalletIsOpen)
    mWalletConfig->writeEntry("Password", QVariant(port).toByteArray());
}