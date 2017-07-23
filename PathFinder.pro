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
    pathfindercanvas.cpp

HEADERS += \
        mainwindow.hpp \
    graph_base.hpp \
    pathfindercanvas.hpp \
    grid.hpp \
    random.hpp

FORMS += \
        mainwindow.ui
