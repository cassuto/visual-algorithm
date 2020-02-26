#-------------------------------------------------
#
# Project created by QtCreator 2020-02-26T22:47:13
#
#-------------------------------------------------

QT       += widgets

TARGET = module-squaredcover
TEMPLATE = lib

DEFINES += MODULESQUAREDCOVER_LIBRARY

SOURCES += modulesquaredcover.cpp

HEADERS += modulesquaredcover.h\
        module-squaredcover_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
