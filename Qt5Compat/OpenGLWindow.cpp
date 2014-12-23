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
#if defined (LINUX) || defined (WIN32)
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif
#ifdef DARWIN
  #include <unistd.h>
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
#endif

OpenGLWindow::OpenGLWindow(QWindow *_parent)
    : QWindow(_parent)
    , m_context(0)
    , m_device(0)
{
  // ensure we render to OpenGL and not a QPainter by setting the surface type
  setSurfaceType(QWindow::OpenGLSurface);

  m_context = new QOpenGLContext(this);
  m_context->setFormat(requestedFormat());
  m_context->create();
  m_context->makeCurrent(this);
  setTitle("Qt5 compat profile OpenGL 2.1");
  m_initialized=false;
}

OpenGLWindow::~OpenGLWindow()
{
  // now we have finished clear the device
  delete m_device;
}



void OpenGLWindow::initialize()
{
  m_context->makeCurrent(this);

  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  int w=this->size().width();
  int h=this->size().height();
  gluPerspective(45,(float)w/h,0.5,100);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(2,2,2,0,0,0,0,1,0);
  startTimer(20);
  glViewport(0,0,width(),height());

}


void OpenGLWindow::exposeEvent(QExposeEvent *event)
{
  // don't use the event
  Q_UNUSED(event);
  // if the window is exposed (visible) render
  if (isExposed())
  {
    render();
  }
}


void OpenGLWindow::render()
{
  if(!m_initialized)
  {
    initialize();
  m_initialized=true;
  }
    // usually we will make this context current and render
  m_context->makeCurrent(this);
  glClear(GL_COLOR_BUFFER_BIT);
  static int rot=0;
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
  ++rot;
  // finally swap the buffers to make visible
  m_context->swapBuffers(this);
}

void OpenGLWindow::timerEvent(QTimerEvent *)
{
  render();
}

void OpenGLWindow::keyPressEvent(QKeyEvent *_event)
{
  switch (_event->key())
  {
   case Qt::Key_Escape : QApplication::exit(EXIT_SUCCESS); break;
  }
}

void OpenGLWindow::resizeEvent(QResizeEvent *)
{
    glViewport(0,0,width(),height());
}
