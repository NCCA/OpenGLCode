TARGET=VertexArrayPoints
OBJECTS_DIR=obj
# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
isEqual(QT_MAJOR_VERSION, 5) {
cache()
}

MOC_DIR=moc
CONFIG-=app_bundle
QT+=gui opengl core
SOURCES+= $$PWD/src/main.cpp \
          $$PWD/src/OpenGLWindow.cpp

HEADERS+= $$PWD/include/OpenGLWindow.h
INCLUDEPATH += include
DESTDIR=./

CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11
macx:DEFINES+=GL_SILENCE_DEPRECATION
