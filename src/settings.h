// This file is generated by kconfig_compiler from playbak.kcfg.
// All changes you do to this file will be lost.
#ifndef SETTINGS_H
#define SETTINGS_H

#include <kconfigskeleton.h>
#include <kdebug.h>

class Settings : public KConfigSkeleton
{
  public:

    static Settings *self();
    ~Settings();

    /**
      Set color of the background
    */
    static
    void setCol_background( const QColor & v )
    {
      if (!self()->isImmutable( QString::fromLatin1( "col_background" ) ))
        self()->mCol_background = v;
    }

    /**
      Get color of the background
    */
    static
    QColor col_background()
    {
      return self()->mCol_background;
    }

    /**
      Set color of the foreground
    */
    static
    void setCol_foreground( const QColor & v )
    {
      if (!self()->isImmutable( QString::fromLatin1( "col_foreground" ) ))
        self()->mCol_foreground = v;
    }

    /**
      Get color of the foreground
    */
    static
    QColor col_foreground()
    {
      return self()->mCol_foreground;
    }


    /**
      Get size of a ball
    */
    static
    int val_time()
    {
      return self()->mVal_time;
    }


    /**
      Get show tray icon
    */
    static
    bool show_tray_icon()
    {
      return self()->mShow_tray_icon;
    }


    /**
      Get show notification
    */
    static
    bool show_notifications()
    {
      return self()->mShow_notifications;
    }

  protected:
    Settings();
    friend class SettingsHelper;


    // Preferences
    QColor mCol_background;
    QColor mCol_foreground;
    int mVal_time;
    bool mShow_tray_icon;
    bool mShow_notifications;

  private:
};

#endif

