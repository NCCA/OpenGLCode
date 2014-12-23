TARGET=Cube
OBJECTS_DIR=obj
# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
isEqual(QT_MAJOR_VERSION, 5) {
cache()
}

MOC_DIR=moc
CONFIG-=app_bundle
QT+= opengl core
SOURCES+= main.cpp \
					OpenGLWindow.cpp

HEADERS+= OpenGLWindow.h

DESTDIR=./

CONFIG += console
CONFIG -= app_bundle

QMAKE_CXXFLAGS+= -msse -msse2 -msse3
macx:QMAKE_CXXFLAGS+= -arch x86_64
macx:INCLUDEPATH+=/usr/local/include/
linux-g++:QMAKE_CXXFLAGS +=  -march=native
linux-g++-64:QMAKE_CXXFLAGS +=  -march=native

# now if we are under unix and not on a Mac (i.e. linux) define GLEW
linux-g++* {
		DEFINES += LINUX
                DEFINES +=GL_GLEXT_PROTOTYPES

}
linux-clang* {
		DEFINES += LINUX
                DEFINES +=GL_GLEXT_PROTOTYPES
}
DEPENDPATH+=include
# if we are on a mac define DARWIN
macx:DEFINES += DARWIN

win32: {
				DEFINES+=_WIN32
}


