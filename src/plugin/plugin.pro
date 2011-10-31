TEMPLATE = lib

#MEEGO_IM_PLUGINS_DIR = $$system( pkgconfig --variable pluginsdir MeegoImFramework )

CONFIG += plugin
CONFIG += meegoimframework
;CONFIG += meegoimquick

QT = core gui declarative

TARGET = cuteinputmethod

OBJECTS_DIR = .tmp
MOC_DIR = .tmp

INCLUDEPATH += ./inputmethod

HEADERS += plugin.h ./inputmethod/inputmethod.h
SOURCES += plugin.cpp ./inputmethod/inputmethod.cpp
