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
const static int s_numPoints=10000;

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
  setTitle("Qt5 compat profile OpenGL 3.2");
  m_initialized=false;
  // first we generate random point x,y,z values
  m_points = new GLfloat[2*s_numPoints];
  for( int i=0; i<2*s_numPoints; ++i)
  {
    m_points[i]= -1.0f + (float)rand()/((float)RAND_MAX/(1.0f- -1.0f));
  }
  m_colours = new GLfloat[3*s_numPoints];
  for( int i=0; i<3*s_numPoints; ++i)
  {
    m_colours[i]= 0.0f + (float)rand()/((float)RAND_MAX/(1.0f));
  }

}

OpenGLWindow::~OpenGLWindow()
{
  // now we have finished clear the device
  delete m_device;
  delete [] m_points;
  delete [] m_colours;
}



void OpenGLWindow::initialize()
{
  m_context->makeCurrent(this);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);			   // Grey Background
  glColor3f(1,1,1);
  glPointSize(4);
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
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, m_points);
  glColorPointer(3,GL_FLOAT,0,m_colours);
  glDrawArrays(GL_POINTS, 0, s_numPoints);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
  // finally swap the buffers to make visible
  m_context->swapBuffers(this);
}

void OpenGLWindow::resizeEvent(QResizeEvent *)
{
    glViewport(0,0,width(),height());
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
