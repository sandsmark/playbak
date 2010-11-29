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

#include <KDE/KApplication>
#include <KDE/KAboutData>
#include <KDE/KCmdLineArgs>
#include <KDE/KLocale>

#include <mainwindow.h>

static const char description[] =
    I18N_NOOP("A KDE 4 Multimedia Player");

static const char version[] = "%{VERSION}";

int main(int argc, char **argv)
{
    KAboutData about("playbak", 0, ki18n("PlaybaK"), version, ki18n(description),
                    KAboutData::License_GPL_V3, ki18n("(C) 2010 PlaybaK Development Team"), KLocalizedString(), 0, "%{EMAIL}");
    about.setProgramIconName("playbak");
    about.addAuthor( ki18n("Borek, Andres"),   ki18n("Programmer and Spanish translator"),    "andres.b.dev@gmail.com" );
    about.addAuthor( ki18n("Borek, Danilo"),   ki18n("Programmer and Spanish translator"),    "d4gnu.dev@gmail.com" );
    about.addAuthor( ki18n("Castro, Gil"),     ki18n("Programmer and Portuguese translator"), "gilfmc@gmail.com" );
    about.addAuthor( ki18n("Comito, Vicenzo"), ki18n("Programmer and Italian translator"),    "clynamen@gmail.com" );

    KCmdLineArgs::init(argc, argv, &about);

    KCmdLineOptions options;
    options.add("+[URL]", ki18n( "Document to open" ));
    KCmdLineArgs::addCmdLineOptions(options);
    KApplication app;

    MainWindow *widget = new MainWindow;

    // see if we are starting with session management
    if (app.isSessionRestored())
    {
//         RESTORE(playbak);
    }
    else
    {
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
