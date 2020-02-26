#-------------------------------------------------
#
# Project created by QtCreator 2020-02-26T22:32:51
#
#-------------------------------------------------

QT       += widgets

TARGET = module-prim
TEMPLATE = lib

DEFINES += MODULEPRIM_LIBRARY

SOURCES += moduleprim.cpp

HEADERS += moduleprim.h\
        module-prim_global.h

INCLUDEPATH += $$PWD/../frontend/include
DEPENDPATH += $$PWD/../frontend/include

unix {
    target.path = /usr/lib
    INSTALLS += target
}
