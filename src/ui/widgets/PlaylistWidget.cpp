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

#include <iostream>

#include <QKeyEvent>
#include <QWheelEvent>

#include <AudioMediaItem.h>
#include <PlaylistAudioItemWidget.h>
#include <PlaylistWidget.h>
#include <ui_PlaylistWidget.h>

PlaylistWidget::PlaylistWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlaylistWidget)
{
    ui->setupUi(this);
    mContentHeight = 0;
    mLastScrollbarValue = 0;
    mReorganize = false;
    mReorganize = false;
    ui->mVerticalScrollBar->setMinimum(0);
    ui->mVerticalScrollBar->setMaximum(0);
    connect(ui->mVerticalScrollBar,SIGNAL(valueChanged(int)),this,SLOT(moveContent(int)));
    mShiftPressed = false;
  }

PlaylistWidget::~PlaylistWidget()
{
    delete ui;
}

void PlaylistWidget::addItems(QList<MediaItem*> *items){
  // TODO In parallel
  
  int startFrom = ui->mContent->children().size();
  for(int i = 0; i < items->size();++i)
  {
    // We create the corresponded PlaylistItem acord the type
    //We use the mime type to see the file type
    if (!(*items)[i]->mimetype().isEmpty())
    {
      // If is an audio, we create an PlaylistAudioItemWidget
      if (
            // Audio normal
            ((*items)[i]->mimetype().contains("audio",Qt::CaseInsensitive)) or
            // Streaming
            ((*items)[i]->mimetype().contains("stream",Qt::CaseInsensitive)) or
            ((*items)[i]->mimetype().contains("mpegurl",Qt::CaseInsensitive)) or
            ((*items)[i]->mimetype().contains("octeta-stream",Qt::CaseInsensitive))
         )
      {
        AudioMediaItem *audioMediaItem = new AudioMediaItem(*(*items)[i]);

        PlaylistAudioItemWidget *mediaItem_new = new PlaylistAudioItemWidget(*audioMediaItem,this);

        mediaItem_new->setParent(ui->mContent);
        mediaItem_new->move(0,mContentHeight);
        mediaItem_new->mParentChildPos = ui->mContent->children().size() - 1;

        if ( (mContentHeight - ui->mContent->height()) > 0 )
            ui->mVerticalScrollBar->setMaximum(mContentHeight - ui->mContent->height());
        else
            ui->mVerticalScrollBar->setMaximum(0);
        
        mContentHeight += mediaItem_new->height();

        connect(mediaItem_new,SIGNAL(play(int)),this,SIGNAL(play(int)));
        connect(mediaItem_new,SIGNAL(resized(int)),this,SLOT(reorganize(int)));
        connect(mediaItem_new,SIGNAL(removed(int)),this,SLOT(removeItem(int)));
        connect(mediaItem_new,SIGNAL(selected(int)),this,SLOT(selectManager(int)));
      }
      else if ((*items)[i]->mimetype().contains("video",Qt::CaseInsensitive))
      {
      }
      else if ((*items)[i]->mimetype().contains("image",Qt::CaseInsensitive))
      {
      }
    }
    // If the file have not mime type, we try to identify the type using Phonon
    // (for audio an video), and QImage (for images)
    else
    {
      // We try to read like an image
        // If is it, create the item and return
      // We read the file wiht Phonon
        // If is Phonon can read
          // If have an video, is an video an we create the item and return
          // else, is an audio an we create the item and return
    }
  }
  if (ui->mContent->children().size() > startFrom)
    for (int i = startFrom; i < ui->mContent->children().size(); ++i)
      static_cast< QWidget* >(ui->mContent->children().at(i))->show();
}

void PlaylistWidget::clearPlaylist()
{
  int size = ui->mContent->children().size();
  for (int i = 0; i < size; ++i)
    removeItem(0);
}

void PlaylistWidget::reorganize(int widget_ptr){
  /*
   Primero aumentamos el tamaño del contenido y el rango del scrollbar
   */
  PlaylistAbstractMediaItem *w = static_cast<PlaylistAbstractMediaItem*>(ui->mContent->children().at(widget_ptr));
  if (w->mLastHeight < w->height())
    mContentHeight += (w->height() - w->mLastHeight);
  else
    mContentHeight -= (w->mLastHeight - w->height());

  if ( (mContentHeight - ui->mContent->height()) > 0 )
    ui->mVerticalScrollBar->setMaximum(mContentHeight - ui->mContent->height());
  else
    ui->mVerticalScrollBar->setMaximum(0);

  if (widget_ptr == -1)
    return;
  mReorganize = true;
  mReorganizeItem = widget_ptr;
}

void PlaylistWidget::moveContent(int offset){
  QWidget *w;
  for (int i = 0; i < ui->mContent->children().size(); ++i ){
    w = static_cast<QWidget*>(ui->mContent->children().at(i));
    // Restamos el offset ya que si el valor es 10, los elementos tienen que moverse 10px para arriba
    if (mLastScrollbarValue < offset)
      w->move(0,w->y() - (offset - mLastScrollbarValue) );
    else
      w->move(0,w->y() + (mLastScrollbarValue - offset));
  }
  mLastScrollbarValue = offset;
}

void PlaylistWidget::wheelEvent(QWheelEvent *e){
  int numDegrees = e->delta() / 2;
  ui->mVerticalScrollBar->setValue(ui->mVerticalScrollBar->value() - numDegrees);
  e->accept();
}

void PlaylistWidget::removeItem(int item){
//   If the item is out of the range, we do nothing
  if ( ( item < 0 ) ||
       ( item >= ui->mContent->children().size() ) )
    return;
  PlaylistAbstractMediaItem *w;
  w = static_cast<PlaylistAbstractMediaItem*>(ui->mContent->children().at(item));
  int itemH(w->height());
  mContentHeight -= itemH;
  if ( (mContentHeight - ui->mContent->height()) > 0 )
//     ui->mVerticalScrollBar->setMaximum(mContentHeight - ui->mContent->height());
    ui->mVerticalScrollBar->setMaximum(mContentHeight);
  else
    ui->mVerticalScrollBar->setMaximum(0);
  w->setParent(0x0L);
  w->destroy();
  emit removedItem(item);
  for (int i = item; i < ui->mContent->children().size(); ++i ){
    w = static_cast<PlaylistAbstractMediaItem*>(ui->mContent->children().at(i));
    w->mParentChildPos--;
//    int tmp = w->height();
    w->move(0, w->y() - itemH);
//    itemH = tmp;
  }

}

void PlaylistWidget::removeSelecteds()
{
  QObject *item;
  foreach(item, ui->mContent->children())
  {
    PlaylistItemWidget *l_item;
    if ( l_item = qobject_cast< PlaylistItemWidget* >(item))
      if (l_item->getSelected())
        removeItem(l_item->mParentChildPos);
  }
}

void PlaylistWidget::selectManager(int item){
  if (!mShiftPressed)
    for (int i = 0; i < ui->mContent->children().size(); ++i )
     static_cast<PlaylistAbstractMediaItem*>(ui->mContent->children().at(i))->setSelected(false);
 static_cast<PlaylistAbstractMediaItem*>(ui->mContent->children().at(item))->setSelected(true);
}

void PlaylistWidget::paintEvent(QPaintEvent *){
  if (mReorganize) {
    QWidget *lastW = 0x0L;
    QWidget *w;
    w = static_cast<QWidget*>(ui->mContent->children().at(mReorganizeItem));
    int y(w->pos().y());
    for (int i = mReorganizeItem; i < ui->mContent->children().size(); ++i ){
      w = static_cast<QWidget*>(ui->mContent->children().at(i));
      if (lastW) {
        w->move(0, y += lastW->height());
      }
      lastW = w;
    }
    mReorganize = false;
//    if(height() >= mHeightContent &&
//       static_cast<PlaylistAbstractItem*>(ui->mContent->children().at(mWidgetPtr))->mExpandAnimation->state() != QAbstractAnimation::Running )
//      ui->mVerticalScrollBar->hide();
//    else
//      ui->mVerticalScrollBar->show();
  }
}

void PlaylistWidget::resizeEvent ( QResizeEvent *event ){
  if ( (mContentHeight - ui->mContent->height()) > 0 )
    ui->mVerticalScrollBar->setMaximum(mContentHeight - ui->mContent->height());
  else
    ui->mVerticalScrollBar->setMaximum(0);
  QWidget *w;
  for (int i = 0; i < ui->mContent->children().size(); ++i ){
    w = static_cast<QWidget*>(ui->mContent->children().at(i));
    w->resize(ui->mContent->width(),w->height());
  }
  QWidget::resizeEvent(event);
}

void PlaylistWidget::keyPressEvent(QKeyEvent *e){
  if (e->key() | Qt::Key_Shift)
    mShiftPressed = true;
}

void PlaylistWidget::keyReleaseEvent(QKeyEvent *e){
  if (e->key() | Qt::Key_Shift)
    mShiftPressed = false;
}
