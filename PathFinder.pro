QT       += core gui widgets

CONFIG += c++14

TEMPLATE = subdirs
SUBDIRS = src test

TARGET = PathFinder
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        mainwindow.cpp \
    main.cpp \
    pathfindercanvas.cpp \
    adpter.cpp \
    graph.cpp \
    graphicsview.cpp

HEADERS += \
        mainwindow.hpp \
    pathfindercanvas.hpp \
    grid.hpp \
    random.hpp \
    adpter.hpp \
    graph.hpp \
    graphicsview.hpp

FORMS += \
        mainwindow.ui
