/*
* PlaybaK - A KDE Multimedia Player.
* Copyright (C) 2010 PlaybaK Development Team (see AUTHORS file)
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, see http://www.gnu.org/licenses
* or write to the Free Software Foundation,Inc., 51 Franklin Street,
* Fifth Floor, Boston, MA 02110-1301  USA
*/

#include <QSharedMemory>

#include <KDE/KApplication>
#include <KDE/KAboutData>
#include <KDE/KCmdLineArgs>
#include <KDE/KLocale>
#include <KDE/KUniqueApplication>

#include <iostream>

#include <mainwindow.h>

static const char description[] =
    I18N_NOOP("A KDE 4 Multimedia Player");

static const char version[] = "%{VERSION}";

int main(int argc, char **argv)
{

    // We create only one instance of the aplication
    // NOTE: (Andrés): I not use KUniqueApplication bacause break the interfece (don't wort the interfece, the buttons and etc)
    QSharedMemory shared("Playbak Shared Memory");
    // If we can not create the sared memory is because one instance of the aplications created it
    if(shared.create(1,QSharedMemory::ReadWrite)==false)
    {
      std::cout << "===========================\n";
      std::cout << "PlaybaK is already running.\n";
      std::cout << "===========================\n";
      return 0;      
    }
  
    KAboutData about("playbak", 0, ki18n("PlaybaK"), version, ki18n(description),
                     KAboutData::License_GPL_V3, ki18n("(C) 2010 PlaybaK Development Team"), KLocalizedString(), 0, "%{EMAIL}");
    about.setProgramIconName("playbak");
    about.addAuthor( ki18n("Borek, Andres José"),      ki18n("Programmer and Spanish translator"), "andres.b.dev@gmail.com" );
    about.addAuthor( ki18n("Borek, Danilo Vladimiro"), ki18n("Programmer and Spanish translator"), "d4gnu.dev@gmail.com" );
    about.addAuthor( ki18n("Castro, Gil"),     ki18n("Programmer and Portuguese translator"), "gilfmc@gmail.com" );
    about.addAuthor( ki18n("Comito, Vicenzo"), ki18n("Programmer and Italian translator"),    "clynamen@gmail.com" );
    
    KCmdLineArgs::init(argc, argv, &about);
    KCmdLineOptions options;
    KCmdLineArgs::addCmdLineOptions(options);
    options.add("+[URL]", ki18n( "Document to open" ));
    KApplication app;
    app.setApplicationName("PlaybaK");

    MainWindow *widget = new MainWindow;
    widget->setObjectName("PlaybaK#");
    
    app.enableSessionManagement();

    if (app.isSessionRestored())
    {
        RESTORE(MainWindow);
    }
    else
    {
//       qDebug(":::Iniciado normalmente...");
      
        // no session.. just start up normally
        KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
        if (args->count() == 0)
        {
            //playbak *widget = new playbak;
            widget->show();
        }
        else
        {
            int i = 0;
            for (; i < args->count(); i++)
            {
                //playbak *widget = new playbak;
                widget->show();
            }
        }
        args->clear();
    }

    return app.exec();
}
