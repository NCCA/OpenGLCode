#ifndef OPENGLWINDOW_H_
#define OPENGLWINDOW_H_
#include <QKeyEvent>
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

    ~OpenGLWindow() override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief render method called every update
    //----------------------------------------------------------------------------------------------------------------------
    void paintGL() override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief pure virtual initialize method we override in our base class to do our drawing
    /// this is only called one time, just after we have a valid GL context use this to init any global GL elements
    //----------------------------------------------------------------------------------------------------------------------
   void initializeGL() override;

  private:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief event called by the timer to allow use to re-draw / animate
    //----------------------------------------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief flag to indicate if the window is initialised
    //----------------------------------------------------------------------------------------------------------------------
    bool m_initialized;

    void timerEvent(QTimerEvent *) override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief process key events
    //----------------------------------------------------------------------------------------------------------------------
    void keyPressEvent(QKeyEvent *) override;

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief resize event
    //----------------------------------------------------------------------------------------------------------------------
    void resizeGL(int _w , int _h) override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief create a cube and stuff it into a VBO on the GPU
    /// @param[in] _scale a scale factor for the unit vertices
    //----------------------------------------------------------------------------------------------------------------------
    void createCube(GLfloat _scale);
  /// @brief a pointer to our VBO data
    GLuint m_vboPointer;
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
