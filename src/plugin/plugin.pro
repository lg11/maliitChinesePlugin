TEMPLATE = lib

#MEEGO_IM_PLUGINS_DIR = $$system( pkgconfig --variable pluginsdir MeegoImFramework )

CONFIG += plugin
CONFIG += meegoimframework
CONFIG += meegotouch
;CONFIG += meegoimquick

QT = core gui declarative

TARGET = cuteinputmethod

OBJECTS_DIR = .tmp
MOC_DIR = .tmp

INCLUDEPATH += ./inputmethod ./settings ./toolbar

HEADERS += plugin.h ./inputmethod/inputmethod.h ./settings/settings.h ./settings/widget.h ./toolbar/toolbar.h
SOURCES += plugin.cpp ./inputmethod/inputmethod.cpp ./settings/settings.cpp ./toolbar/toolbar.cpp
