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
const static float gridSize=1.5;
const	static int steps=24;

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

}

OpenGLWindow::~OpenGLWindow()
{
  // now we have finished clear the device
  delete m_device;
  std::cout<<"deleting buffer\n";
  glDeleteBuffers(1,&m_vboPointer);
}



void OpenGLWindow::initialize()
{
  m_context->makeCurrent(this);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);			   // Grey Background
  m_vboPointer=makeGrid(gridSize,steps,m_vboSize);
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

GLuint  OpenGLWindow::makeGrid( GLfloat _size, int _steps, int &o_dataSize  )
{
	// allocate enough space for our verts
	// as we are doing lines it will be 2 verts per line
	// and we need to add 1 to each of them for the <= loop
	// and finally muliply by 12 as we have 12 values per line pair
	o_dataSize= (_steps+2)*12;
	float *vertexData= new float[o_dataSize];
	// k is the index into our data set
	int k=-1;
	// claculate the step size for each grid value
	float step=_size/(float)_steps;
	// pre-calc the offset for speed
	float s2=_size/2.0f;
	// assign v as our value to change each vertex pair
	float v=-s2;
	// loop for our grid values
	for(int i=0; i<=_steps; ++i)
	{
		// vertex 1 x,y,z
		vertexData[++k]=-s2; // x
		vertexData[++k]=v; // y
		vertexData[++k]=0.0; // z

		// vertex 2 x,y,z
		vertexData[++k]=s2; // x
		vertexData[++k]=v; // y
		vertexData[++k]=0.0; // z

		// vertex 3 x,y,z
		vertexData[++k]=v;
		vertexData[++k]=s2;
		vertexData[++k]=0.0;

		// vertex 4 x,y,z
		vertexData[++k]=v;
		vertexData[++k]=-s2;
		vertexData[++k]=0.0;
		// now change our step value
		v+=step;
	}


	// now we will create our VBO first we need to ask GL for an Object ID
	GLuint VBOBuffers;
	// now create the VBO
	glGenBuffers(1, &VBOBuffers);
	// now we bind this ID to an Array buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBOBuffers);
	// finally we stuff our data into the array object
	// First we tell GL it's an array buffer
	// then the number of bytes we are storing (need to tell it's a sizeof(FLOAT)
	// then the pointer to the actual data
	// Then how we are going to draw it (in this case Statically as the data will not change)
	glBufferData(GL_ARRAY_BUFFER, o_dataSize*sizeof(GL_FLOAT) , vertexData, GL_STATIC_DRAW);

	// now we can delete our client side data as we have stored it on the GPU
	delete [] vertexData;
	// now return the VBO Object pointer to our program so we can use it later for drawing
	return VBOBuffers;
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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // enable  vertex array drawing
  glEnableClientState(GL_VERTEX_ARRAY);
  // bind our VBO data to be the currently active one
  glBindBuffer(GL_ARRAY_BUFFER, m_vboPointer);
  // tell GL how this data is formated in this case 3 floats tightly packed starting at the begining
  // of the data (0 = stride, 0 = offset)
  glVertexPointer(3,GL_FLOAT,0,0);
  // draw the VBO as a series of GL_LINES starting at 0 in the buffer and _vboSize*GLfloat
  glDrawArrays( GL_LINES, 0, m_vboSize);

  // now turn off the VBO client state as we have finished with it
  glDisableClientState(GL_VERTEX_ARRAY);
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
