######################################################################
# Automatically generated by qmake (2.01a) Mon Jan 17 20:04:29 2011
######################################################################

TEMPLATE = app
TARGET = main
DEPENDPATH += .
INCLUDEPATH += .

QT += dbus declarative

OBJECTS_DIR = tmp
MOC_DIR = tmp

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += x11 xext
}

# Input
HEADERS += host.h view.h adaptor.h ../engine/engine.h
SOURCES += main.cpp host.cpp view.cpp adaptor.cpp ../engine/engine.cpp
