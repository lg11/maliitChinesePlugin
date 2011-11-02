#include "settings.h"
#include "widget.h"

#include <QDebug>

namespace settings {

const QString EnabledSubViewsKey( "/meegotouch/inputmethods/onscreen/enabled" ) ;

Settings::Settings() : enabledKeyboardsConf( EnabledSubViewsKey ) {
    connect( &enabledKeyboardsConf, SIGNAL(valueChanged()), this, SLOT(slotEnabledKeyboardsChanged()) ) ;
}

Settings::~Settings() {
}

QString Settings::title() {
    return QString("cuteinputmethod") ;
}

QString Settings::icon() {
    return QString("");
}

QGraphicsWidget *Settings::createContentWidget( QGraphicsWidget *parent ) {
    //qDebug() << "createContentWidget()" ;
    return new Widget( this, parent) ;
}

QStringList Settings::selectedKeyboards() const {
    QStringList list ;
    list << "libcuteinputmethod.so" << " " ;
    return list ;
}

void Settings::slotEnabledKeyboardsChanged() {
    emit enabledKeyboardsChanged() ;
}

}
