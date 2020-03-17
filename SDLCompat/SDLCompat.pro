QT-=core
QT-=opengl
QT-=xml
# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
isEqual(QT_MAJOR_VERSION, 5) {
cache()
DEFINES +=QT5BUILD
}
TARGET=SDLOpenGL
CONFIG-=app_bundle
CONFIG+=c++11
DESTDIR=./
OBJECTS_DIR=obj
SOURCES=$$PWD/src/main.cpp
macx:DEFINES+=GL_SILENCE_DEPRECATION
QMAKE_CXXFLAGS+=$$system(sdl2-config  --cflags)
message(output from sdl2-config --cflags added to CXXFLAGS= $$QMAKE_CXXFLAGS)

LIBS+=$$system(sdl2-config  --libs)
message(output from sdl2-config --libs added to LIB=$$LIBS)


macx:INCLUDEPATH+=/usr/local/include
LIBS += -L/usr/local/lib
linux:LIBS+= -lGL -lGLU















