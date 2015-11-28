/*
 * Basic GL Window modified from the example here
 * http://qt-project.org/doc/qt-5.0/qtgui/openglwindow.html
 * adapted to use NGL
 */
#include "OpenGLWindow.h"
#include <QtCore/QCoreApplication>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>
#include <QKeyEvent>
#include <QApplication>
#include <iostream>
#ifdef __APPLE__
  #include <glu.h>
#else
  #include <GL/glu.h>
#endif


OpenGLWindow::OpenGLWindow()
{
  setTitle("Qt5 compat profile OpenGL 2.1");
}

OpenGLWindow::~OpenGLWindow()
{
}



void OpenGLWindow::initializeGL()
{

  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  int w=this->size().width();
  int h=this->size().height();
  gluPerspective(45,(float)w/h,0.5,100);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(2,2,2,0,0,0,0,1,0);

  glViewport(0,0,width(),height());
  startTimer(10);

}

void OpenGLWindow::paintGL()
{
  glViewport(0,0,m_width,m_height);
  glClear(GL_COLOR_BUFFER_BIT);
  //static int rot=0;
  glPushMatrix();
    glRotated(rot,0,1,0);
    glBegin(GL_TRIANGLES);
      glColor3f(1,0,0);
      glVertex3d(0,1,0);
      glColor3f(0,1,0);
      glVertex3d(1,-1,0);
      glColor3f(0,0,1);
      glVertex3d(-1,-1,0);
    glEnd();
  glPopMatrix();
 // ++rot;
}

void OpenGLWindow::timerEvent(QTimerEvent *)
{
  rot++;
  update();
}

void OpenGLWindow::keyPressEvent(QKeyEvent *_event)
{
  switch (_event->key())
  {
   case Qt::Key_Escape : QApplication::exit(EXIT_SUCCESS); break;
  }
}

void OpenGLWindow::resizeGL(QResizeEvent *_event)
{
  /*
Note: This is merely a convenience function in order to provide an API that is compatible with QOpenGLWidget. Unlike with QOpenGLWidget, derived classes are free to choose to override
resizeEvent() instead of this function.
Note: Avoid issuing OpenGL commands from this function as there may not be
 a context current when it is invoked. If it cannot be avoided, call makeCurrent().
*/
  m_width=_event->size().width()*devicePixelRatio();
  m_height=_event->size().height()*devicePixelRatio();

}

void OpenGLWindow::resizeGL(int _w, int _h)
{
  /*
Note: This is merely a convenience function in order to provide an API that is compatible with QOpenGLWidget. Unlike with QOpenGLWidget, derived classes are free to choose to override
resizeEvent() instead of this function.
Note: Avoid issuing OpenGL commands from this function as there may not be
 a context current when it is invoked. If it cannot be avoided, call makeCurrent().
*/
  m_width=_w;
  m_height=_h;

}

