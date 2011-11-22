TEMPLATE = lib
CONFIG += qt plugin
QT += declarative

TARGET = engine

OBJECTS_DIR = tmp
MOC_DIR = tmp


HEADERS += \
    plugin.h \
    engine.h \
    worker.h \

SOURCES += \
    plugin.cpp \
    worker.cpp \

