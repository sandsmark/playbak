#include "PlaybakSettings.hpp"

#include <QEventLoop>
#include <QByteArray>
#include <QMap>
#include <QVariant>

PlaybakSettings::PlaybakSettings() :
  mConfigFile(QString("PlaybaK"))
{
  mAudioConfigGroup = mConfigFile.group("Audio");
  mVideoConfigGroup = mConfigFile.group("Audio");
  mGeneralConfigGroup = mConfigFile.group("General");
  mWalletReadedSusefully = false;
//   QObject::connect(mWalletConfig, SIGNAL(walletOpened(bool)),this, SLOT(isWalletOpen(bool)));
  QEventLoop loop;
  QObject::connect(mWalletConfig,SIGNAL(walletOpened(bool)),&loop,SLOT(quit()));
  loop.exec();
  isWalletOpen(true);
  mWalletConfig = KWallet::Wallet::openWallet(KWallet::Wallet::NetworkWallet(),
                                              0,
                                              KWallet::Wallet::Asynchronous);
  // NOTE: No se el valor correcto del volumen
  mAudioPreamp = QVariant(mAudioConfigGroup.readEntry( "Preamplifier", qreal(0.5) )).toReal();
  mBrightness = QVariant(mVideoConfigGroup.readEntry( "Brightness", qreal(0.5) )).toReal();
  mContrast = QVariant(mVideoConfigGroup.readEntry( "Contrast", qreal(0.5) )).toReal();
  // TODO: read the equalizer
  mHue = QVariant(mVideoConfigGroup.readEntry( "Hue", qreal(0.5) )).toReal();
  // TODO: Read the lenguage of the sistem to default, not en
  mLanguage = QVariant(mGeneralConfigGroup.readEntry( "Language", QString("en") )).toString();
  mSaturation = QVariant(mVideoConfigGroup.readEntry( "Saturation", qreal(0.5) )).toReal();
  mVolume = QVariant(mVideoConfigGroup.readEntry( "Volume", qreal(0.5) )).toReal();                                                
}

void PlaybakSettings::isWalletOpen(bool ok)
{
  mWalletIsOpen = ok;
  if (ok)
    loadDatabaseConfig();
}

void PlaybakSettings::loadDatabaseConfig()
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
  mWalletReadedSusefully = true;
  
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

QString PlaybakSettings::host()
{
  return mHost;
}

QString PlaybakSettings::user()
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

void PlaybakSettings::setAudioPromp(qreal audioPreamp)
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

void PlaybakSettings::setHost(QString host)
{
  mHost = host;
  if (mWalletIsOpen)
    mWalletConfig->writeEntry("Host", host.toUtf8());
}

void PlaybakSettings::setUser(QString user)
{
  mUser = user;
  if (mWalletIsOpen)
    mWalletConfig->writeEntry("User", user.toUtf8());
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