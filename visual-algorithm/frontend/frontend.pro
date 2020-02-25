#-------------------------------------------------
#
# Project created by QtCreator 2020-02-25T09:20:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = frontend
TEMPLATE = app


SOURCES += \
    formalgorithmmenu.cpp \
    main.cpp \
    mainwindow.cpp \
    moduleloader.cpp \
    formalgorithmview.cpp \
    models.cpp \
    modelhanoiimpl.cpp

HEADERS  += dialog.h \
    formalgorithmmenu.h \
    mainwindow.h \
    moduleloader.h \
    include/errorcodes.h \
    formalgorithmview.h \
    include/imodel.h \
    include/imodule.h \
    models.h \
    modelhanoiimpl.h

RESOURCES += \
    resources.qrc

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
