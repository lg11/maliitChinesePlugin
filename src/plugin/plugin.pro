TEMPLATE = lib

CONFIG += plugin

#CONFIG += meegoimframework
#CONFIG += meegotouch
#CONFIG += meegoimquick

CONFIG += link_pkgconfig
PKGCONFIG += maliit-plugins-0.80
target.path += $$system(pkg-config --variable pluginsdir maliit-plugins-0.80)
INCLUDEPATH += $$system(pkg-config --cflags maliit-plugins-0.80 | tr \' \' \'\\n\' | grep ^-I | cut -d I -f 2-)
INSTALLS += target


QT = core gui declarative

TARGET = linputmethod

OBJECTS_DIR = .tmp
MOC_DIR = .tmp

INCLUDEPATH += ./inputmethod ./settings ./view ./engine

HEADERS += \
	plugin.h \
	./engine/engine.h \
	./engine/worker.h \
	./engine/keyfilter.h \
	./inputmethod/inputmethod.h \
    ./view/inputmethodview.h \

	#./toolbar/data.h ./toolbar/item.h ./toolbar/icon.h
	#./settings/settings.h ./settings/widget.h \
	
SOURCES += \
	plugin.cpp \
	./engine/engine.cpp \
	./engine/worker.cpp \
	./engine/keyfilter.cpp \
	./inputmethod/inputmethod.cpp \
    ./view/inputmethodview.cpp \

	#./toolbar/data.cpp ./toolbar/item.cpp ./toolbar/icon.cpp
	#./settings/settings.cpp \
