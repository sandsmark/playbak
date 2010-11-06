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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"
#include <QPushButton>
#include <KIcon>
#include <QTime>
#include "PlaybaKFadingButton.h"
#include "mainwindow.moc"
#include <kaction.h>
#include <kactioncollection.h>
#include <kstandardaction.h>

MainWindow::MainWindow(QWidget *parent) :
KXmlGuiWindow(parent),
ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->prevMedia->setIcon(KIcon("media-skip-backward"));
	ui->playMedia->setIcon(KIcon("media-playback-start"));
	ui->nextMedia->setIcon(KIcon("media-skip-forward"));
	ui->muteSwitch->setIcon(KIcon("preferences-desktop-sound"));
	ui->playlistFilterConfigButton->setIcon(KIcon("preferences-other"));
	ui->playMedia->setOverIcon("/home/gil/playglow.png");
	setAcceptDrops(true);
	setupActions();
	setupGUI(Create | Keys);
	mip1 = new MediaInfoPage(ui->mediaInfo);
	ui->mediaInfo->insertWidget(0, mip1);
	mip2 = new MediaInfoInteractivePage(ui->mediaInfo);
	ui->mediaInfo->insertWidget(1, mip2);
	ui->mediaInfo->setCurrentIndex(0);
	//mip1->setStyleSheet(QString::fromUtf8("#page {\n"
	//																			"background-color:\n"
	//																			"qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ccc, stop: 1.0 #c2c2c2);\n"
	//																			"border: 1px solid rgb(150, 150, 150);\n"
	//																			"border-radius: 5px;\n"
	//																			"}"));
	connect(mip1, SIGNAL(mouseOver()), SLOT(showMediaInfoPage2()));
	connect(mip1, SIGNAL(mouseLeave()), SLOT(showMediaInfoPage1()));
	connect(mip2, SIGNAL(mouseLeave()), SLOT(showMediaInfoPage1()));
	connect(mip2, SIGNAL(ratingChanged(int)), mip1, SLOT(setRating(int)));
	test = new PlaybaKAnimatedSliderWidget(this);
	test2 = new PlaybaKAnimatedSliderWidget(this);
	test3 = new PlaybaKAnimatedSliderWidget(this);
	test4 = new PlaybaKAnimatedSliderWidget(this);
	test5 = new PlaybaKAnimatedSliderWidget(this);
	test6 = new PlaybaKAnimatedSliderWidget(this);
	test7 = new PlaybaKAnimatedSliderWidget(this);
	ui->st->addWidget(test);
	ui->st->addWidget(test2);
	ui->st->addWidget(test3);
	ui->st->addWidget(test4);
	ui->st->addWidget(test5);
	ui->st->addWidget(test6);
	ui->st->addWidget(test7);
	connect(ui->playMedia, SIGNAL(clicked()), SLOT(testclick()));
	QTime time = QTime::currentTime();
	qsrand((uint)time.msec());
}

void MainWindow::showMediaInfoPage2()
{
	if(ui->mediaInfo->currentIndex() != 1)
		ui->mediaInfo->setCurrentIndex(1);
}

void MainWindow::showMediaInfoPage1()
{
	if(ui->mediaInfo->currentIndex() != 0)
		ui->mediaInfo->setCurrentIndex(0);
}

void MainWindow::testclick()
{
	test->setValueAnimating(qrand() % ((99 + 1) - 0) + 0);
	test2->setValueAnimating(qrand() % ((99 + 1) - 0) + 0);
	test3->setValueAnimating(qrand() % ((99 + 1) - 0) + 0);
	test4->setValueAnimating(qrand() % ((99 + 1) - 0) + 0);
	test5->setValueAnimating(qrand() % ((99 + 1) - 0) + 0);
	test6->setValueAnimating(qrand() % ((99 + 1) - 0) + 0);
	test7->setValueAnimating(qrand() % ((99 + 1) - 0) + 0);
}


void MainWindow::optionsPreferences()
{
    // this show the configuration dialog

    //avoid to have 2 dialogs shown
    if ( KConfigDialog::showDialog ( "settings" ) )
    {
        return;
    }

    dialog = new KConfigDialog ( this, "settings", Settings::self() );
    dialog->setFaceType ( KPageDialog::List );
    QWidget *baseSettingsDlg = new QWidget;
    ui_prefs_base.setupUi ( baseSettingsDlg );
    dialog->addPage ( baseSettingsDlg, i18n ( "General" ), "preferences-other" );
    dialog->setAttribute ( Qt::WA_DeleteOnClose );
    dialog->show();
}

void MainWindow::setupActions()
{
    // It adds the action in the menu bar, created on playbakui.rc model.
    KStandardAction::quit ( qApp, SLOT ( closeAllWindows() ), actionCollection() );
    KStandardAction::preferences ( this, SLOT ( optionsPreferences() ), actionCollection() );
}

MainWindow::~MainWindow()
{
  delete ui;
}
