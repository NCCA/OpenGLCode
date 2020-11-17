#include <gl/glew.h>
#include "OpenGLWindow.h"
#include <array>
#include <QApplication>
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
void OpenGLWindow::createCube( GLfloat _scale)
{

   // vertex coords array
  std::array<GLfloat,12*6> vertices = {{
                         1, 1, 1, -1, 1, 1, -1,-1, 1,  1,-1, 1,  // v0-v1-v2-v3
                         1, 1, 1,  1,-1, 1,  1,-1,-1,  1, 1,-1,  // v0-v3-v4-v5
                         1, 1, 1,  1, 1,-1, -1, 1,-1, -1, 1, 1,  // v0-v5-v6-v1
                        -1, 1, 1, -1, 1,-1, -1,-1,-1, -1,-1, 1,  // v1-v6-v7-v2
                        -1,-1,-1,  1,-1,-1,  1,-1, 1, -1,-1, 1,  // v7-v4-v3-v2
                         1,-1,-1, -1,-1,-1, -1, 1,-1,  1, 1,-1   // v4-v7-v6-v5
                        }};
  // normal array
  std::array<GLfloat,12*6> normals = {{
                        0, 0, 1,   0, 0, 1,  0, 0, 1,  0, 0, 1,     // v0-v1-v2-v3
                        1, 0, 0,   1, 0, 0,  1, 0, 0,  1, 0, 0,     // v0-v3-v4-v5
                        0, 1, 0,   0, 1, 0,  0, 1, 0,  0, 1, 0,     // v0-v5-v6-v1
                       -1, 0, 0,  -1, 0, 0, -1, 0, 0, -1, 0, 0,     // v1-v6-v7-v2
                        0,-1, 0,   0,-1, 0,  0,-1, 0,  0,-1, 0,     // v7-v4-v3-v2
                        0, 0,-1,   0, 0, -1, 0, 0,-1,  0, 0,-1      // v4-v7-v6-v5
                      }};

  // colour array
  std::array<GLfloat,12*6> colours =
                      {{
                        1,1,1,  1,1,0,  1,0,0,  1,0,1,  // v0-v1-v2-v3
                        1,1,1,  1,0,1,  0,0,1,  0,1,1,  // v0-v3-v4-v5
                        1,1,1,  0,1,1,  0,1,0,  1,1,0,  // v0-v5-v6-v1
                        1,1,0,  0,1,0,  0,0,0,  1,0,0,  // v1-v6-v7-v2
                        0,0,0,  0,0,1,  1,0,1,  1,0,0,  // v7-v4-v3-v2
                        0,0,1,  0,0,0,  0,1,0,  0,1,1		// v4-v7-v6-v5
                      }};
  // first we scale our vertices to _scale
  for(auto &v : vertices)
  {
    v*=_scale;
  }
  // now create the VBO
  glGenBuffers(1, &m_vboPointer);
  // now we bind this ID to an Array buffer
  glBindBuffer(GL_ARRAY_BUFFER, m_vboPointer);

  // this time our buffer is going to contain verts followed by normals
  // so allocat     e enough space for all of them
  glBufferData(GL_ARRAY_BUFFER, 72*3*sizeof(GLfloat) , 0, GL_STATIC_DRAW);
  // now we copy the data for the verts into our buffer first
  glBufferSubData(GL_ARRAY_BUFFER,0,24*3*sizeof(GLfloat),&vertices[0]);
  // now we need to tag the normals onto the end of the verts
  glBufferSubData(GL_ARRAY_BUFFER,24*3*sizeof(GLfloat),24*3*sizeof(GLfloat),&normals[0]);

  // now we need to tag the colours onto the end of the normals
  glBufferSubData(GL_ARRAY_BUFFER,48*3*sizeof(GLfloat),24*3*sizeof(GLfloat),&colours[0]);

}

void OpenGLWindow::initializeGL()
{
  glewInit();

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);			   // Grey Background
  createCube(0.6);
  std::cout<<m_vboPointer<<"\n";
  glViewport(0,0,width(),height());
  startTimer(10);
}


void OpenGLWindow::paintGL()
{
  glViewport(0,0,m_width,m_height);
  //GLubyte indices[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
  std::vector<GLubyte> indices(24);
  std::iota(std::begin(indices),std::end(indices),0);

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
    glVertexPointer(3,GL_FLOAT,0,nullptr);
    // now we tell it where the nornals are (thes are basically at the end of the verts
    glNormalPointer(GL_FLOAT, 0,reinterpret_cast<float *>(24*3*sizeof(float)));
    // now we tell it where the colours are (thes are basically at the end of the normals
    glColorPointer(3,GL_FLOAT, 0,reinterpret_cast<float *>(48*3*sizeof(float)));
    glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,&indices[0]);
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
   case Qt::Key_W : glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); break;
   case Qt::Key_S : glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); break;

  }
}

void OpenGLWindow::resizeGL(int _w, int _h)
{
  m_width  = static_cast<int>( _w * devicePixelRatio() );
  m_height = static_cast<int>( _h * devicePixelRatio() );

}
