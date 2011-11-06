TEMPLATE = app

#MEEGO_IM_PLUGINS_DIR = $$system( pkgconfig --variable pluginsdir MeegoImFramework )

CONFIG += meegotouch

QT = core gui

TARGET = main

OBJECTS_DIR = .tmp
MOC_DIR = .tmp

SOURCES += main.cpp
