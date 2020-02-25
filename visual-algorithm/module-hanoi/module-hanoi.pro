#-------------------------------------------------
#
# Project created by QtCreator 2020-02-25T09:24:38
#
#-------------------------------------------------

QT       -= gui

TARGET = module-hanoi
TEMPLATE = lib

DEFINES += MODULEHANOI_LIBRARY

SOURCES += modulehanoi.cpp

HEADERS += modulehanoi.h\
        module-hanoi_global.h

INCLUDEPATH += $$PWD/../frontend/include
DEPENDPATH += $$PWD/../frontend/include

unix {
    target.path = /usr/lib
    INSTALLS += target
}
