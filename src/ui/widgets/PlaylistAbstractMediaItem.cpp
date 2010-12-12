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

#include <QResizeEvent>

#include <KDE/KIcon>

#include <PlaylistAbstractMediaItem.h>
#include <ui_PlaylistAbstractMediaItem.h>

KIcon PlaylistAbstractMediaItem::add_icon("list-add");
KIcon PlaylistAbstractMediaItem::remove_icon("list-remove");
QVector<KIcon*> *PlaylistAbstractMediaItem::mExpandButtonIcon = 0x0L;

PlaylistAbstractMediaItem::PlaylistAbstractMediaItem(QWidget *parent) :
    PlaylistItemWidget(parent),
    ui(new Ui::PlaylistAbstractItem)
{
  if (mExpandButtonIcon == 0x0L){
    mExpandButtonIcon = new QVector<KIcon*>;
    mExpandButtonIcon->push_back(&add_icon);
    mExpandButtonIcon->push_back(&remove_icon);
    
  }
    ui->setupUi(this);
    mExtraHeight = 0;
    mExpandAnimation = 0x0L;
    mExpandButtonAnimation = 0x0L;
    mExpandingContracting = false;
}

PlaylistAbstractMediaItem::~PlaylistAbstractMediaItem()
{
  delete mExpandAnimation;
  delete mExpandButtonAnimation;
  mExpandButtonIcon->clear();

  delete ui;
}

void PlaylistAbstractMediaItem::mouseDoubleClickEvent(QMouseEvent *){
  emit play(mParentChildPos);
}

void PlaylistAbstractMediaItem::resizeEvent ( QResizeEvent *event ){
  mLastHeight = event->oldSize().height();
  QWidget::resizeEvent(event);
  if (mParentChildPos != -1 && event->oldSize().height() != height()){
    emit resized(mParentChildPos);
  }
}

#include "PlaylistAbstractMediaItem.moc"
