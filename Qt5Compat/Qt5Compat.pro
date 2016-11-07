TARGET=Qt5Compat
OBJECTS_DIR=obj
# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
isEqual(QT_MAJOR_VERSION, 5) {
cache()
}
QT+=opengl
linux:LIBS+=-lGLU

MOC_DIR=moc
CONFIG-=app_bundle
CONFIG+=c++11
QT+= opengl core
SOURCES+= $$PWD/src/main.cpp \
          $$PWD/src/OpenGLWindow.cpp

HEADERS+= $$PWD/include/OpenGLWindow.h
INCLUDEPATH+=$$PWD/include
DESTDIR=./

CONFIG += console
CONFIG -= app_bundle
macx:QMAKE_MAC_SDK = macosx10.12

