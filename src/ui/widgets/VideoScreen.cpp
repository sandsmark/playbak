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

#include "VideoScreen.h"
#include <Phonon/VideoWidget>
#include <qevent.h>

void VideoScreen::mousePressEvent(QMouseEvent* event)
{
  setFocus(Qt::MouseFocusReason);
  QWidget::mousePressEvent(event);
}

void VideoScreen::mouseDoubleClickEvent(QMouseEvent* e)
{
  toggleFullScreen();
}

void VideoScreen::toggleFullScreen()
{
  if (!isFullScreen()) {
    mWindowFlags = windowFlags() & (Qt::Window);
    mGeometry = geometry();
    setWindowFlags((windowFlags() | Qt::Window));
  #ifdef Q_WS_X11
    show();
    raise();
    setWindowState(windowState() | Qt::WindowFullScreen);
  #else
    setWindowState(windowState() | Qt::WindowFullScreen);
    show();
  #endif
  } else {
    setWindowFlags((windowFlags() ^ (Qt::Window)) | mWindowFlags);
    setWindowState(windowState() & ~Qt::WindowFullScreen);
    setGeometry(mGeometry);
    show();
  }
  setFocus(Qt::NoFocusReason);
}


void VideoScreen::keyPressEvent(QKeyEvent* e)
{
  switch(e->key()){
    case Qt::Key_Escape:
    case Qt::Key_F:
      toggleFullScreen();
      break;
  }
  
  
//     QWidget::keyPressEvent(e);
}

VideoScreen::VideoScreen(QWidget* parent) :
  QWidget(parent)
{
//   setEnabled(true);
}

#include "../include/VideoScreen.moc"