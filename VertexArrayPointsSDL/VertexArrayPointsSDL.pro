QT -= core
QT -=opengl
QT -=xml
# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
isEqual(QT_MAJOR_VERSION, 5) {
cache()
}
TARGET=VertexArrayPoints
CONFIG+=c++11
CONFIG-=app_bundle
DESTDIR=./
OBJECTS_DIR=obj
SOURCES=$$PWD/src/main.cpp
macx:DEFINES+=DARWIN
QMAKE_CXXFLAGS+= -msse -msse2 -msse3
macx:QMAKE_CXXFLAGS+= -arch x86_64
macx:INCLUDEPATH+=/usr/local/boost/
linux-g++:QMAKE_CXXFLAGS +=  -march=native
linux-g++-64:QMAKE_CXXFLAGS +=  -march=native

QMAKE_CXXFLAGS+=$$system(sdl2-config  --cflags)
message(output from sdl2-config --cflags added to CXXFLAGS= $$QMAKE_CXXFLAGS)

LIBS+=$$system(sdl2-config  --libs)
message(output from sdl2-config --libs added to LIB=$$LIBS)

macx:QMAKE_MAC_SDK = macosx10.12

macx:INCLUDEPATH+=/usr/local/include
LIBS += -L/usr/local/lib
# now if we are under unix and not on a Mac (i.e. linux) define GLEW
linux-g++* {
                DEFINES +=GL_GLEXT_PROTOTYPES
                LIBS+=-lGLU

}
linux-clang* {
                DEFINES +=GL_GLEXT_PROTOTYPES
                LIBS+=-lGLU
}
