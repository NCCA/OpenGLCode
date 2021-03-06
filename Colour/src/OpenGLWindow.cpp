/*
 * Basic GL Window modified from the example here
 * http://qt-project.org/doc/qt-5.0/qtgui/openglwindow.html
 * adapted to use NGL
 */
#include "OpenGLWindow.h"
#include <random>
constexpr int s_numPoints=1000000;

OpenGLWindow::OpenGLWindow()
{
  setTitle("Qt5 compat profile OpenGL 3.2");
  // first we generate random point x,y,z values
  // using a smart pointer so the reset method creates a new array
  m_points.reset( new GLfloat[2*s_numPoints]);
  m_colours.reset (new GLfloat[3*s_numPoints]);
  // now to use the new C++ 11 rng functions
  std::random_device rd;
  //create a mersenne twister generator
  std::mt19937 gen(rd());
  // create real distribution functions for colour and points
  std::normal_distribution<float> colour(0.5f);
  std::uniform_real_distribution<float> point(-1.0f,1.0f);

  for( size_t i=0; i<2*s_numPoints; ++i)
  {
    m_points[i]= point(gen);
  }
  for( size_t i=0; i<3*s_numPoints; ++i)
  {
    m_colours[i]= 0.2f+colour(gen);
  }
    startTimer(10);
}

OpenGLWindow::~OpenGLWindow()
{
}



void OpenGLWindow::initializeGL()
{

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);			   // Grey Background
  glColor3f(1,1,1);
  glPointSize(18);
}



void OpenGLWindow::paintGL()
{
  glViewport(0,0,m_width,m_height);
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, m_points.get());
  glColorPointer(3,GL_FLOAT,0,m_colours.get());
  glDrawArrays(GL_POINTS, 0, s_numPoints);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}




void OpenGLWindow::resizeGL(int _w, int _h)
{
  m_width=_w*devicePixelRatio();
  m_height=_h*devicePixelRatio();

}




void OpenGLWindow::timerEvent(QTimerEvent *)
{
  // now to use the new C++ 11 rng functions
  std::random_device rd;
  //create a mersenne twister generator
  std::mt19937 gen(rd());
  // create real distribution functions for colour and points
  std::uniform_real_distribution<float> point(-1.0f,1.0f);

  for( size_t i=0; i<2*s_numPoints; ++i)
  {
    m_points[i]= point(gen);
  }
  update();
}

void OpenGLWindow::keyPressEvent(QKeyEvent *_event)
{
  switch (_event->key())
  {
   case Qt::Key_Escape : QApplication::exit(EXIT_SUCCESS); break;
  }
}
