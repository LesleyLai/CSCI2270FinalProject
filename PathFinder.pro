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
    adpter.cpp \
    graph.cpp \
    graphicsview.cpp \
    pathfinder.cpp

HEADERS += \
        mainwindow.hpp \
    grid.hpp \
    random.hpp \
    adpter.hpp \
    graph.hpp \
    graphicsview.hpp \
    type.hpp \
    pathfinder.hpp \
    priority_queue.hpp

FORMS += \
        mainwindow.ui
