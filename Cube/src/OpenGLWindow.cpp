/*
 * Basic GL Window modified from the example here
 * http://qt-project.org/doc/qt-5.0/qtgui/openglwindow.html
 * adapted to use NGL
 */
#include "OpenGLWindow.h"
#include <iostream>
OpenGLWindow::OpenGLWindow()
{
  // ensure we render to OpenGL and not a QPainter by setting the surface type
  setSurfaceType(QWindow::OpenGLSurface);

  setTitle("Qt5 compat profile OpenGL 3.2");

}

OpenGLWindow::~OpenGLWindow()
{
  std::cout<<"deleting buffer\n";
  glDeleteBuffers(1,&m_vboPointer);

}

//----------------------------------------------------------------------------------------------------------------------
/// \brief create a cube and stuff it into a VBO on the GPU
/// @param[in] _scale a scale factor for the unit vertices
void OpenGLWindow::createCube( GLfloat _scale,GLuint &o_vboPointer )
{

   // vertex coords array
  GLfloat vertices[] = {
                         1, 1, 1, -1, 1, 1, -1,-1, 1,  1,-1, 1,  // v0-v1-v2-v3
                         1, 1, 1,  1,-1, 1,  1,-1,-1,  1, 1,-1,  // v0-v3-v4-v5
                         1, 1, 1,  1, 1,-1, -1, 1,-1, -1, 1, 1,  // v0-v5-v6-v1
                        -1, 1, 1, -1, 1,-1, -1,-1,-1, -1,-1, 1,  // v1-v6-v7-v2
                        -1,-1,-1,  1,-1,-1,  1,-1, 1, -1,-1, 1,  // v7-v4-v3-v2
                         1,-1,-1, -1,-1,-1, -1, 1,-1,  1, 1,-1   // v4-v7-v6-v5
                        };
  // normal array
  GLfloat normals[] = {
                        0, 0, 1,   0, 0, 1,  0, 0, 1,  0, 0, 1,     // v0-v1-v2-v3
                        1, 0, 0,   1, 0, 0,  1, 0, 0,  1, 0, 0,     // v0-v3-v4-v5
                        0, 1, 0,   0, 1, 0,  0, 1, 0,  0, 1, 0,     // v0-v5-v6-v1
                       -1, 0, 0,  -1, 0, 0, -1, 0, 0, -1, 0, 0,     // v1-v6-v7-v2
                        0,-1, 0,   0,-1, 0,  0,-1, 0,  0,-1, 0,     // v7-v4-v3-v2
                        0, 0,-1,   0, 0, -1, 0, 0,-1,  0, 0,-1      // v4-v7-v6-v5
                      };

  // color array
  GLfloat colours[] =
                      {
                        1,1,1,  1,1,0,  1,0,0,  1,0,1,  // v0-v1-v2-v3
                        1,1,1,  1,0,1,  0,0,1,  0,1,1,  // v0-v3-v4-v5
                        1,1,1,  0,1,1,  0,1,0,  1,1,0,  // v0-v5-v6-v1
                        1,1,0,  0,1,0,  0,0,0,  1,0,0,  // v1-v6-v7-v2
                        0,0,0,  0,0,1,  1,0,1,  1,0,0,  // v7-v4-v3-v2
                        0,0,1,  0,0,0,  0,1,0,  0,1,1		// v4-v7-v6-v5
                      };
  // first we scale our vertices to _scale
  for(int i=0; i<24*3; ++i)
  {
    vertices[i]*=_scale;
  }
  // now create the VBO
  glGenBuffers(1, &o_vboPointer);
  // now we bind this ID to an Array buffer
  glBindBuffer(GL_ARRAY_BUFFER, o_vboPointer);

  // this time our buffer is going to contain verts followed by normals
  // so allocate enough space for all of them
  glBufferData(GL_ARRAY_BUFFER, 72*3*sizeof(GL_FLOAT) , 0, GL_STATIC_DRAW);
  // now we copy the data for the verts into our buffer first
  glBufferSubData(GL_ARRAY_BUFFER,0,24*3*sizeof(GL_FLOAT),vertices);
  // now we need to tag the normals onto the end of the verts
  glBufferSubData(GL_ARRAY_BUFFER,24*3*sizeof(GL_FLOAT),24*3*sizeof(GL_FLOAT),normals);

  // now we need to tag the colours onto the end of the normals
  glBufferSubData(GL_ARRAY_BUFFER,48*3*sizeof(GL_FLOAT),24*3*sizeof(GL_FLOAT),colours);

}

void OpenGLWindow::initializeGL()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);			   // Grey Background
  createCube(0.6,m_vboPointer);
  std::cout<<m_vboPointer<<"\n";
  glViewport(0,0,width(),height());
  startTimer(10);
}


void OpenGLWindow::paintGL()
{
  glViewport(0,0,m_width,m_height);
  GLubyte indices[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
  // this macro is used to define the offset into the VBO data for our normals etc
  // it needs to be a void pointer offset from 0
  #define BUFFER_OFFSET(i) ((float *)NULL + (i))

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
    static int xrot=0;
    static int yrot=0;
    glRotatef(xrot++,1,0,0);
    glRotatef(yrot++,0,1,0);
    // enable  vertex array drawing
    glEnableClientState(GL_VERTEX_ARRAY);
    // enable Normal array
    glEnableClientState(GL_NORMAL_ARRAY);
    // enable the colour array
    glEnableClientState(GL_COLOR_ARRAY);

    // bind our VBO data to be the currently active one
    glBindBuffer(GL_ARRAY_BUFFER, m_vboPointer);
    // we need to tell GL where the verts start
    glVertexPointer(3,GL_FLOAT,0,0);
    // now we tell it where the nornals are (thes are basically at the end of the verts
    glNormalPointer(GL_FLOAT, 0,BUFFER_OFFSET(24*3));
    // now we tell it where the colours are (thes are basically at the end of the normals
    glColorPointer(3,GL_FLOAT, 0,BUFFER_OFFSET(48*3));
    glDrawElementsInstancedARB(GL_QUADS,24,GL_UNSIGNED_BYTE,indices,1);
    // now turn off the VBO client state as we have finished with it
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
  glPopMatrix();  // finally swap the buffers to make visible
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
