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

#include <QAction>
#include <QContextMenuEvent>
#include <QMenu>
#include <QResizeEvent>
#include <QVBoxLayout>

#include <KDE/KIcon>

#include <AudioMediaItem.h>
#include <PlaylistAudioItemExtra.h>
#include <PlaylistAudioItemWidget.h>
#include <PlaylistWidget.h>
#include <ui_PlaylistAudioItemExtra.h>
#include <ui_PlaylistAudioItemWidget.h>
#include <QLayout>
#include <qfile.h>
#include <qfileinfo.h>

PlaylistAudioItemWidget::PlaylistAudioItemWidget(QString mediaItem,QWidget *parent) :
    PlaylistAbstractMediaItem(parent),
    ui(new Ui::PlaylistAudioItemWidget)
{
    mMediaItem = 0x0L;
    mMediaItem = new AudioMediaItem(mediaItem,true);
    ui->setupUi(this);
    static int  sMinHeight(ui->mTopWidget->sizeHint().height());
    static int  sMaxHeight(ui->mContent->sizeHint().height());
    static int  sMinWidth(ui->mTimeLabel->sizeHint().width() + ui->mExpandButton->sizeHint().width());
    
    setMinimumHeight(sMinHeight);
    setMaximumHeight(sMaxHeight);
    
    // When the metadata is loaded/changed, we change the labels
    connect(mMediaItem,SIGNAL(metadataChanged()),this,SLOT(loadMetadata()));
    loadMetadata();
    
    mExpandButtonIconIt = mExpandButtonIcon->begin();
    
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    
    ui->mExtra->setLayout(layout);
    
    ui->mTitleLabel->setMinimumWidth(0);
    
    ui->mExpandButton->setIcon(*(*mExpandButtonIconIt));
    
    resize(parent->width(),minimumHeight());
    
    ui->mContent->resize(width(),ui->mContent->height());
    
    mExpandAnimation = new QPropertyAnimation(this,"size");
    mExpandAnimation->setDuration(750);
    
    connect(ui->mExpandButton,SIGNAL(clicked()), this, SLOT(createExtra()));
    
    mExpandButtonAnimation = new QPropertyAnimation(ui->mExpandButton,"maximumWidth");
    mExpandButtonAnimation->setDuration(500);
    mExpandButtonAnimation->setStartValue(0);
    mExpandButtonAnimation->setEndValue(24);
    mExpandButtonAnimation->setEasingCurve(QEasingCurve::InCubic);
    
    connect(mExpandButtonAnimation,SIGNAL(finished()),this,SLOT(toggleButtonAnimation()));
    
    ui->mExpandButton->setMaximumWidth(0);
    
}

PlaylistAudioItemWidget::PlaylistAudioItemWidget(AudioMediaItem& mediaItem, QWidget* parent):
PlaylistAbstractMediaItem(parent),
ui(new Ui::PlaylistAudioItemWidget)
{
//   QTime t;
//   t.start();
  mMediaItem = &mediaItem;
  ui->setupUi(this);

  static int  sMinHeight(ui->mTopWidget->sizeHint().height());
  static int  sMaxHeight(ui->mContent->sizeHint().height());
  static int  sMinWidth(ui->mTimeLabel->sizeHint().width() + ui->mExpandButton->sizeHint().width());
  
  setMinimumHeight(sMinHeight);
  setMaximumHeight(sMaxHeight);

  // When the metadata is loaded/changed, we change the labels
  connect(mMediaItem,SIGNAL(metadataChanged()),this,SLOT(loadMetadata()));
  loadMetadata();
  
  mExpandButtonIconIt = mExpandButtonIcon->begin();
  
  QVBoxLayout *layout = new QVBoxLayout;
  layout->setContentsMargins(0,0,0,0);
  
  ui->mExtra->setLayout(layout);
  
  ui->mTitleLabel->setMinimumWidth(0);
  
  ui->mExpandButton->setIcon(*(*mExpandButtonIconIt));
  
  resize(parent->width(),minimumHeight());
  
  ui->mContent->resize(width(),ui->mContent->height());
  
  mExpandAnimation = new QPropertyAnimation(this,"size");
  mExpandAnimation->setDuration(750);
  
  connect(ui->mExpandButton,SIGNAL(clicked()), this, SLOT(createExtra()));
  
  mExpandButtonAnimation = new QPropertyAnimation(ui->mExpandButton,"maximumWidth");
  mExpandButtonAnimation->setDuration(500);
  mExpandButtonAnimation->setStartValue(0);
  mExpandButtonAnimation->setEndValue(24);
  mExpandButtonAnimation->setEasingCurve(QEasingCurve::InCubic);
  
  connect(mExpandButtonAnimation,SIGNAL(finished()),this,SLOT(toggleButtonAnimation()));
  
  ui->mExpandButton->setMaximumWidth(0);

}

void PlaylistAudioItemWidget::firstConstructPlaylistAudioItemWidget()
{
}

PlaylistAudioItemWidget::~PlaylistAudioItemWidget()
{
  mExpandButtonIcon->clear();
    delete ui;
}

void PlaylistAudioItemWidget::toggleAnimation(){
  mExpandAnimation->stop();
  if(mExpandAnimation->endValue().toSize().height() == minimumHeight()) {
    mExpandAnimation->setEndValue(QSize(width(), minimumHeight()));
    mExpandAnimation->setStartValue(QSize(width(), ui->mContent->sizeHint().height()));
  }
  else {
    mExpandAnimation->setStartValue(QSize(width(), minimumHeight()));
    mExpandAnimation->setEndValue(QSize(width(), ui->mContent->sizeHint().height()));
  }
  mExpandingContracting = false;
}

void PlaylistAudioItemWidget::toggleButtonAnimation(){
  QVariant start, end;
  start = mExpandButtonAnimation->startValue();
  end = mExpandButtonAnimation->endValue();
  mExpandButtonAnimation->stop();
  mExpandButtonAnimation->setStartValue(end);
  mExpandButtonAnimation->setEndValue(start);
}

void PlaylistAudioItemWidget::enterEvent(QEvent *){
  mExpandButtonAnimation->stop();
  mExpandButtonAnimation->setStartValue(ui->mExpandButton->width());
  mExpandButtonAnimation->setEndValue(24);
  mExpandButtonAnimation->start();
}

void PlaylistAudioItemWidget::leaveEvent(QEvent *){
  mExpandButtonAnimation->stop();
  mExpandButtonAnimation->setStartValue(ui->mExpandButton->width());
  mExpandButtonAnimation->setEndValue(0);
  mExpandButtonAnimation->start();
}

void PlaylistAudioItemWidget::loadMetadata()
{
  if (mMediaItem != 0x0L)
  {
    if (!mMediaItem->title().isEmpty())
      ui->mTitleLabel->setText(((AudioMediaItem*)(mMediaItem))->title());
    else
    {
      QFileInfo file_info(mMediaItem->url().toLocalFile());
      ui->mTitleLabel->setText(file_info.baseName());
    }
    ui->mTimeLabel->setText(QString::number(((AudioMediaItem*)(mMediaItem))->duration().minute()) + QString(":") + QString::number(((AudioMediaItem*)(mMediaItem))->duration().second()));
    QTime duration = ((AudioMediaItem*)(mMediaItem))->duration();
    if (duration.hour() > 0 && duration.hour() < 10)
      ui->mTimeLabel->setText( duration.toString("h:mm:ss") );
    else if (duration.hour() >= 10)
      ui->mTimeLabel->setText( duration.toString("hh:mm:ss") );
    else
      ui->mTimeLabel->setText( duration.toString("mm:ss") );
   
    /*
     * TODO:
     * Load Album image
     */
    if ((ui->mExtra->layout() != 0x0L) && (!ui->mExtra->layout()->children().isEmpty())){
      PlaylistAudioItemExtra *extra =  qobject_cast< PlaylistAudioItemExtra* >(ui->mExtra->layout()->children().at(0));
      qobject_cast< PlaylistAudioItemExtra* >(extra)->ui->mAlbum->setText(((AudioMediaItem*)(mMediaItem))->album());
      qobject_cast< PlaylistAudioItemExtra* >(extra)->ui->mArtist->setText(((AudioMediaItem*)(mMediaItem))->artist());
      qobject_cast< PlaylistAudioItemExtra* >(extra)->ui->mRatingLabel->setText(QString::number(((AudioMediaItem*)(mMediaItem))->rating()));
      qobject_cast< PlaylistAudioItemExtra* >(extra)->ui->mTrack->setText(QString::number(((AudioMediaItem*)(mMediaItem))->trackNumber()));
    }
  }
}

bool PlaylistAudioItemWidget::event(QEvent *e){
  if(e->type() == QEvent::MouseButtonPress){
//    setSelected(true);
    emit selected(mParentChildPos);
    return true;
  }
  else if (e->type() == QEvent::MouseButtonDblClick){
    emit play(mParentChildPos);
    return true;
  }
  return QWidget::event(e);
}

void PlaylistAudioItemWidget::createExtra(){

  PlaylistAudioItemExtra *extra = new PlaylistAudioItemExtra;
  mExtraHeight = extra->sizeHint().height();
  ui->mExtra->layout()->addWidget(extra);
  ui->mExtra->resize(width(),extra->sizeHint().height());
  disconnect(ui->mExpandButton,SIGNAL(clicked()), this, SLOT(createExtra()));

  mExpandAnimation->setStartValue(QSize(width(), minimumHeight()));
  mExpandAnimation->setEndValue(QSize(width(), extra->sizeHint().height() + minimumHeight()));
  mExpandAnimation->setEasingCurve(QEasingCurve::OutCubic);

  connect(mExpandAnimation,SIGNAL(finished()),this,SLOT(toggleAnimation()));
  connect(ui->mExpandButton,SIGNAL(clicked()), this,SLOT(expandContract()));
  connect(extra,SIGNAL(moreInfo()), this,SLOT(emitMoreInfo()));

  setMaximumHeight(extra->sizeHint().height() + minimumHeight());

  if (++mExpandButtonIconIt == mExpandButtonIcon->end() )
    mExpandButtonIconIt = mExpandButtonIcon->begin();
  ui->mExpandButton->setIcon(**mExpandButtonIconIt);

  mExpandAnimation->start();

  qobject_cast< const PlaylistAudioItemExtra* >(extra)->ui->mAlbum->setText(((AudioMediaItem*)(mMediaItem))->album());
  qobject_cast< const PlaylistAudioItemExtra* >(extra)->ui->mArtist->setText(((AudioMediaItem*)(mMediaItem))->artist());
  qobject_cast< const PlaylistAudioItemExtra* >(extra)->ui->mRatingLabel->setText(QString::number(((AudioMediaItem*)(mMediaItem))->rating()));
  qobject_cast< const PlaylistAudioItemExtra* >(extra)->ui->mTrack->setText(QString::number(((AudioMediaItem*)(mMediaItem))->trackNumber()));
  /*
   * TODO:
   * Load extra information like top artist
   */
}

void PlaylistAudioItemWidget::contextMenuEvent(QContextMenuEvent *e){
  QMenu menu(this);
  QAction *play   = new QAction(KIcon("media-playback-start"),tr("Play"), this);
  QAction *remove = new QAction(KIcon("list-remove"),tr("Remove"), this);
  menu.addAction(play);
  menu.addAction(remove);
  connect(remove,SIGNAL(triggered()),this,SLOT(emitRemoved()));
  connect(play,SIGNAL(triggered()),this,SIGNAL(play()));
  menu.exec(e->globalPos());
}

void PlaylistAudioItemWidget::expandContract() {
  if (++mExpandButtonIconIt == mExpandButtonIcon->end() )
    mExpandButtonIconIt = mExpandButtonIcon->begin();
  ui->mExpandButton->setIcon(**mExpandButtonIconIt);
  if (mExpandingContracting) {
    mExpandAnimation->stop();
    if(mExpandAnimation->endValue().toSize().height() != minimumHeight()) {
      mExpandAnimation->setStartValue(size());
      mExpandAnimation->setEndValue(QSize(width(), minimumHeight()));
    }
    else {
      mExpandAnimation->setStartValue(size());
      mExpandAnimation->setEndValue(QSize(width(), ui->mContent->sizeHint().height()));
    }
    mExpandAnimation->start();
    return;
  }
  QVariant tmp;
  tmp = mExpandAnimation->startValue();
  mExpandAnimation->stop();
  mExpandAnimation->setStartValue(mExpandAnimation->endValue());
  mExpandAnimation->setEndValue(tmp);
  mExpandingContracting = true;
  mExpandAnimation->start();
}
void PlaylistAudioItemWidget::emitMoreInfo(){
  emit moreInfo("<Nombre del medio>");
}

void PlaylistAudioItemWidget::emitRemoved(){
  if (mParentChildPos != -1)
    emit removed(mParentChildPos);
}

void PlaylistAudioItemWidget::resizeEvent ( QResizeEvent *event ){
  mLastHeight = event->oldSize().height();
  ui->mContent->resize(parentWidget()->width(), mExtraHeight + minimumHeight());
  mExpandAnimation->setStartValue( QSize(parentWidget()->width(),mExpandAnimation->startValue().toSize().height()) );
  mExpandAnimation->setEndValue( QSize(parentWidget()->width(),mExpandAnimation->endValue().toSize().height()) );
  // Emitimos la señal redimencionado si cambia el alto y si ya está dentro de un playlist
  // emitimos solo cuando cambia el alto ya que el ancho lo cambia el padre (el playlist)
  if (mParentChildPos != -1 && mExpandAnimation->state() == QAbstractAnimation::Running)
    emit resized(mParentChildPos);
}

#include "PlaylistAudioItemWidget.moc"