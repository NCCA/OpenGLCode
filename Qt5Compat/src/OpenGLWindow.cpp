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
  #include <OpenGL/OpenGL.h>
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

  glMatrixMode(GL_PROJECTION);
  int w=width();
  int h=height();
  gluPerspective(45,(float)w/h,0.5,10);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(2,2,2,0,0,0,0,1,0);
  glEnable(GL_DEPTH_TEST);
  startTimer(10);

}

void OpenGLWindow::drawCube(float _w, float _h, float _d)
{
  float w2=_w/2.0f;
  float h2=_h/2.0f;
  float d2=_d/2.0f;

  glBegin(GL_TRIANGLES);
    // front
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(-w2,-h2,d2);
    glVertex3f(w2,-h2,d2);
    glVertex3f(w2,h2,d2);


    // front
    glColor3f(0.5f,0.0f,0.0f);
    glVertex3f(-w2,-h2,-d2);
    glVertex3f(w2,-h2,-d2);
    glVertex3f(w2,h2,-d2);



  glEnd();

}


void OpenGLWindow::paintGL()
{
  glViewport(0,0,m_width,m_height);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
    glRotated(m_rot,0,1,0);
    drawCube(1.0f,1.0f,1.0f);
  glPopMatrix();
}

void OpenGLWindow::timerEvent(QTimerEvent *)
{
  m_rot++;
  update();
}

void OpenGLWindow::keyPressEvent(QKeyEvent *_event)
{
  switch (_event->key())
  {
   case Qt::Key_Escape : QApplication::exit(EXIT_SUCCESS); break;
   case Qt::Key_W : glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
   case Qt::Key_S : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;

   case Qt::Key_F : showFullScreen(); break;
   case Qt::Key_N : showNormal(); break;

  }
  update();
}


void OpenGLWindow::resizeGL(int _w, int _h)
{

  m_width=_w*devicePixelRatio();
  m_height=_h*devicePixelRatio();

}

