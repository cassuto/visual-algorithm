#-------------------------------------------------
#
# Project created by QtCreator 2020-02-26T21:14:25
#
#-------------------------------------------------

QT       += widgets

TARGET = nodule-prim
TEMPLATE = lib

DEFINES += NODULEPRIM_LIBRARY

SOURCES += noduleprim.cpp

HEADERS += noduleprim.h\
        nodule-prim_global.h

INCLUDEPATH += $$PWD/../frontend/include
DEPENDPATH += $$PWD/../frontend/include

unix {
    target.path = /usr/lib
    INSTALLS += target
}
