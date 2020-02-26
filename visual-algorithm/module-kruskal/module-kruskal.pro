#-------------------------------------------------
#
# Project created by QtCreator 2020-02-26T18:58:46
#
#-------------------------------------------------

QT       += widgets

TARGET = module-kruskal
TEMPLATE = lib

DEFINES += MODULEKRUSKAL_LIBRARY

SOURCES += modulekruskal.cpp

HEADERS += modulekruskal.h\
        module-kruskal_global.h

INCLUDEPATH += $$PWD/../frontend/include
DEPENDPATH += $$PWD/../frontend/include

unix {
    target.path = /usr/lib
    INSTALLS += target
}
