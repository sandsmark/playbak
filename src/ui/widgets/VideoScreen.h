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

#ifndef PLAYBAK_VIDEOSCREEN_H
#define PLAYBAK_VIDEOSCREEN_H

#include <Phonon/VideoPlayer>

class VideoScreen : public QWidget {
  Q_OBJECT
public:
//   virtual bool isFullScreen();
protected:
  virtual void mousePressEvent ( QMouseEvent * event );
  virtual void mouseDoubleClickEvent( QMouseEvent * e );
  
  /*!
   * The key press events are only captured in fullscreen mode, because first are
   * captured by MainWindow.
   */
  virtual void keyPressEvent(QKeyEvent *e);
// signals:
//   virtual void toggleFullScreen(QMouseEvent * e);
public slots:
  virtual void toggleFullScreen();
//   VideoScreen(QWidget* parent = 0);
private:
  QRect mGeometry;
  Qt::WindowFlags mWindowFlags;
  bool mFullSreen;
public:
    explicit VideoScreen(QWidget* parent = 0);
};

#endif // PLAYBAK_VIDEOSCREEN_H