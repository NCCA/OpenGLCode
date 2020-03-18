/*
 * Basic GL Window modified from the example here
 * http://qt-project.org/doc/qt-5.0/qtgui/openglwindow.html
 * adapted to use NGL
 */
#include "OpenGLWindow.h"
#include <random>

constexpr size_t s_numPoints=1000;

OpenGLWindow::OpenGLWindow()
{
  setTitle("Qt5 compat profile OpenGL 3.2");
  // first we generate random point x,y,z values
  m_points.reset(new GLfloat[2*s_numPoints]);
  // now to use the new C++ 11 rng functions
  std::random_device rd;
  //create a mersenne twister generator
  std::mt19937 gen(rd());
  gen.seed(1234);
  // create real distribution functions for colour and points
  std::uniform_real_distribution<float> point(-1.0f,1.0f);

  for( size_t i=0; i<2*s_numPoints; ++i)
  {
    m_points[i]= point(gen);
  }

}

OpenGLWindow::~OpenGLWindow()
{
  // now we have finished clear the device
}



void OpenGLWindow::initializeGL()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);			   // Grey Background
  glColor3f(1,1,1);
  glPointSize(20);
  //glDisable(GL_MULTISAMPLE);
}


void OpenGLWindow::resizeGL(int _w, int _h)
{

  m_width=_w*devicePixelRatio();
  m_height=_h*devicePixelRatio();

}




void OpenGLWindow::paintGL()
{
  glViewport(0,0,m_width,m_height);

  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
  //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, m_points.get());

  glDrawArrays(GL_POINTS,0,s_numPoints);

  glDisableClientState(GL_VERTEX_ARRAY);
}

void OpenGLWindow::timerEvent(QTimerEvent *)
{
  update();
}

void OpenGLWindow::keyPressEvent(QKeyEvent *_event)
{
  switch (_event->key())
  {
   case Qt::Key_Escape : QApplication::exit(EXIT_SUCCESS); break;
   case Qt::Key_M : glEnable(GL_MULTISAMPLE); break;
  case Qt::Key_N : glDisable(GL_MULTISAMPLE); break;
  }
  update();
}
