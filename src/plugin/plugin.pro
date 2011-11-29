TEMPLATE = lib

CONFIG += plugin

unix {
    maemo6 {
        CONFIG += meegoimframework
        CONFIG += meegotouch
        CONFIG += meegoimquick
    }
    else {
        CONFIG += meegoimframework
        CONFIG += meegotouch
        CONFIG += meegoimquick

        #CONFIG += link_pkgconfig
        #PKGCONFIG += maliit-plugins-0.80
        #target.path += $$system(pkg-config --variable pluginsdir maliit-plugins-0.80)
        #INCLUDEPATH += $$system(pkg-config --cflags maliit-plugins-0.80 | tr \' \' \'\\n\' | grep ^-I | cut -d I -f 2-)
        #INSTALLS += target
    }
}


QT = core gui declarative

TARGET = linputmethod

OBJECTS_DIR = .tmp
MOC_DIR = .tmp

INCLUDEPATH += ./inputmethod ./settings ./view ./engine ./toolbar ../lookup

HEADERS += \
	plugin.h \
	./engine/worker.h \
	./engine/puncmap.h \
	./engine/engine.h \
	./toolbar/toolbardata.h \
    ./toolbar/toolbaritem.h \
    ./toolbar/toolbaricon.h \
    ./view/inputmethodview.h \
	./inputmethod/keyfilter.h \
	./inputmethod/symbolmap.h \
	./inputmethod/inputmethod.h \

	#./settings/settings.h ./settings/widget.h \
	
SOURCES += \
	plugin.cpp \
	./engine/engine.cpp \
	./engine/worker.cpp \
	./toolbar/toolbardata.cpp \
    ./toolbar/toolbaritem.cpp \
    ./toolbar/toolbaricon.cpp \
    ./view/inputmethodview.cpp \
    ./inputmethod/inputmethod.cpp \

	#./settings/settings.cpp \
