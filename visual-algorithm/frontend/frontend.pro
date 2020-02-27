#-------------------------------------------------
#
# Project created by QtCreator 2020-02-25T09:20:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = frontend
TEMPLATE = app

CONFIG += C++11

QMAKE_CXXFLAGS += -Wno-unused-parameter

SOURCES += \
    formalgorithmmenu.cpp \
    main.cpp \
    mainwindow.cpp \
    moduleloader.cpp \
    formalgorithmview.cpp \
    models.cpp \
    modelhanoiimpl.cpp \
    modelgraphimpl.cpp \
    graphwidget.cpp \
    modellinearlistimpl.cpp \
    modelmatriximpl.cpp \
    runthread.cpp

HEADERS  += dialog.h \
    formalgorithmmenu.h \
    mainwindow.h \
    moduleloader.h \
    include/errorcodes.h \
    formalgorithmview.h \
    include/imodel.h \
    include/imodule.h \
    models.h \
    modelhanoiimpl.h \
    modelgraphimpl.h \
    graphnode.h \
    graphedge.h \
    graphwidget.h \
    modellinearlistimpl.h \
    modelmatriximpl.h \
    runthread.h \
    include/icontrol.h

RESOURCES += \
    resources.qrc

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
LIBS += -lOGDF -lpsapi
