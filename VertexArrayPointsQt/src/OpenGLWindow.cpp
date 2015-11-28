/*
 * Basic GL Window modified from the example here
 * http://qt-project.org/doc/qt-5.0/qtgui/openglwindow.html
 * adapted to use NGL
 */
#include "OpenGLWindow.h"
#include <random>

constexpr int s_numPoints=10000;

OpenGLWindow::OpenGLWindow()
{
  setTitle("Qt5 compat profile OpenGL 3.2");
  // first we generate random point x,y,z values
  m_points.reset(new GLfloat[2*s_numPoints]);
<<<<<<< HEAD

  // now to use the new C++ 11 rng functions
  std::random_device rd;
  //create a mersenne twister generator
  std::mt19937 gen(rd());
  // create real distribution functions for colour and points
  std::uniform_real_distribution<> point(-1.0f,1.0f);

=======
  srand(100);
>>>>>>> 68199245603a8cc30574721015c34d4f8193333c
  for( int i=0; i<2*s_numPoints; ++i)
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
<<<<<<< HEAD
  glPointSize(4);

=======
  glPointSize(12);
>>>>>>> 68199245603a8cc30574721015c34d4f8193333c
}

void OpenGLWindow::resizeEvent(QResizeEvent *_event)
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

<<<<<<< HEAD
=======
void OpenGLWindow::resizeGL(int _w, int _h)
{
  /*
Note: This is merely a convenience function in order to provide an API that is compatible with QOpenGLWidget. Unlike with QOpenGLWidget, derived classes are free to choose to override
resizeEvent() instead of this function.
Note: Avoid issuing OpenGL commands from this function as there may not be
 a context current when it is invoked. If it cannot be avoided, call makeCurrent().
*/
  m_width=_w*devicePixelRatio();
  m_height=_h*devicePixelRatio();

}




>>>>>>> 68199245603a8cc30574721015c34d4f8193333c
void OpenGLWindow::paintGL()
{
  glViewport(0,0,m_width,m_height);

  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
<<<<<<< HEAD

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, m_points.get());
  glDrawArrays(GL_POINTS,0,s_numPoints);


=======
  glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, m_points.get());
    glDrawArrays(GL_POINTS,s_numPoints,s_numPoints);
>>>>>>> 68199245603a8cc30574721015c34d4f8193333c
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
  }
}
