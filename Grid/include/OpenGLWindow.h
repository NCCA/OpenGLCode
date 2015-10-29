#ifndef OPENGLWINDOW_H__
#define OPENGLWINDOW_H__
#include <QOpenGLWindow>

class OpenGLWindow : public QOpenGLWindow
{
  // need to tell Qt to run the MOC
  Q_OBJECT
  public:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief ctor for OpenGL window must set the surface type to OpenGL
    /// @param [in] parent the parent window to the class
    //----------------------------------------------------------------------------------------------------------------------
    explicit OpenGLWindow();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief dtor, remember to remove the device once finished
    //----------------------------------------------------------------------------------------------------------------------

    ~OpenGLWindow();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief render method called every update
    //----------------------------------------------------------------------------------------------------------------------
    void paintGL();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief pure virtual initialize method we override in our base class to do our drawing
    /// this is only called one time, just after we have a valid GL context use this to init any global GL elements
    //----------------------------------------------------------------------------------------------------------------------
   void initializeGL();
  private:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief event called by the timer to allow use to re-draw / animate
    //----------------------------------------------------------------------------------------------------------------------
    void timerEvent(QTimerEvent *);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief process key events
    //----------------------------------------------------------------------------------------------------------------------
    void keyPressEvent(QKeyEvent *);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief resize event
    //----------------------------------------------------------------------------------------------------------------------
    void resizeGL(QResizeEvent *_event);
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
     //----------------------------------------------------------------------------------------------------------------------
     /// @brief window width from resize event
     //----------------------------------------------------------------------------------------------------------------------
     int m_width;
     //----------------------------------------------------------------------------------------------------------------------
     /// @brief window height from resize event
     //----------------------------------------------------------------------------------------------------------------------
     int m_height;

};

#endif