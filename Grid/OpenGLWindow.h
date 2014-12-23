#ifndef OPENGLWINDOW_H__
#define OPENGLWINDOW_H__
#include <QtGui/QWindow>
#include <QtOpenGL>

//----------------------------------------------------------------------------------------------------------------------
/// @class OpenGLWindow
/// @file OpenGLWindow.h
/// @brief this is the base class for all our OpenGL widgets, inherit from this class and overide the methods for
/// OpenGL drawing modified from the Qt demo here  http://qt-project.org/doc/qt-5.0/qtgui/openglwindow.html
/// @author Jonathan Macey
/// @version 1.0
/// @date 10/9/13
/// Revision History :
/// This is an initial version used for the new NGL6 / Qt 5 demos
//----------------------------------------------------------------------------------------------------------------------

// pre declare some classes we need
class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;

class OpenGLWindow : public QWindow
{
  // need to tell Qt to run the MOC
  Q_OBJECT
  public:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief ctor for OpenGL window must set the surface type to OpenGL
    /// @param [in] parent the parent window to the class
    //----------------------------------------------------------------------------------------------------------------------
    explicit OpenGLWindow(QWindow *_parent = 0);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief dtor, remember to remove the device once finished
    //----------------------------------------------------------------------------------------------------------------------

    ~OpenGLWindow();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief render method called every update
    //----------------------------------------------------------------------------------------------------------------------
    void render();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief pure virtual initialize method we override in our base class to do our drawing
    /// this is only called one time, just after we have a valid GL context use this to init any global GL elements
    //----------------------------------------------------------------------------------------------------------------------
   void initialize();

  protected:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this even is called when the window is made visible and will trigger a render
    //----------------------------------------------------------------------------------------------------------------------
    void exposeEvent(QExposeEvent *event);
  private:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the current openGL context, created once when the scene if firt rendered
    //----------------------------------------------------------------------------------------------------------------------
    QOpenGLContext *m_context;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the device used for the actual drawing
    //----------------------------------------------------------------------------------------------------------------------
    QOpenGLPaintDevice *m_device;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief event called by the timer to allow use to re-draw / animate
    //----------------------------------------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief flag to indicate if the window is initialised
    //----------------------------------------------------------------------------------------------------------------------
    bool m_initialized;

    void timerEvent(QTimerEvent *);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief process key events
    //----------------------------------------------------------------------------------------------------------------------
    void keyPressEvent(QKeyEvent *);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief resize event
    //----------------------------------------------------------------------------------------------------------------------
    void resizeEvent(QResizeEvent *);
    //----------------------------------------------------------------------------------------------------------------------
     /// @brief a simple draw grid function
     /// @param[in] _size the size of the grid (width and height)
     /// @param[in] _step sxstep the spacing between grid points
     /// @param[out] o_dataSize the size of the buffer allocated
     /// @returns a pointer to the allocated VBO
     GLuint  makeGrid(GLfloat _size, int _steps,int &o_dataSize);
     /// @brief a pointer to our VBO data
     GLuint m_vboPointer;
     /// @brief store the size of the vbo data
     GLint m_vboSize;

};

#endif
