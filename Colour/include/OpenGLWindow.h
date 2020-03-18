#ifndef OPENGLWINDOW_H_
#define OPENGLWINDOW_H_
#include <QOpenGLWindow>
#include <QtOpenGL>
#include <memory>
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


class OpenGLWindow : public QOpenGLWindow
{
  // need to tell Qt to run the MOC
  Q_OBJECT
  public:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief ctor for OpenGL window must set the surface type to OpenGL
    /// @param [in] parent the parent window to the class
    //----------------------------------------------------------------------------------------------------------------------
    OpenGLWindow();
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
    /// @brief process resize events
    //----------------------------------------------------------------------------------------------------------------------
    void resizeGL(int _w, int _h) override;

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief process resize events
    //----------------------------------------------------------------------------------------------------------------------
    void timerEvent(QTimerEvent *) override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief process key events
    //----------------------------------------------------------------------------------------------------------------------
    void keyPressEvent(QKeyEvent *) override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief pointer to hold array of points
    //----------------------------------------------------------------------------------------------------------------------
    std::unique_ptr<GLfloat []> m_points;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief pointer to hold array of colour values
    //----------------------------------------------------------------------------------------------------------------------
    std::unique_ptr<GLfloat []> m_colours;
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
