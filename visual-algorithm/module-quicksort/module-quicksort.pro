#-------------------------------------------------
#
# Project created by QtCreator 2020-02-26T22:39:44
#
#-------------------------------------------------

QT       += widgets

TARGET = module-quicksort
TEMPLATE = lib

DEFINES += MODULEQUICKSORT_LIBRARY

SOURCES += modulequicksort.cpp

HEADERS += modulequicksort.h\
        module-quicksort_global.h

INCLUDEPATH += $$PWD/../frontend/include
DEPENDPATH += $$PWD/../frontend/include

unix {
    target.path = /usr/lib
    INSTALLS += target
}
