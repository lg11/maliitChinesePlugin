#include <qdeclarative.h>

#include "plugin.h"
#include "inputmethod.h"
#include "toolbar/data.h"
#include "toolbar/item.h"
#include "settings.h"

namespace plugin {

class PluginPrivate {
public :
    QString name ;
    QStringList languages ;
    QSet<MInputMethod::HandlerState> supportedStates ;
    MAbstractInputMethodSettings* settings ;
    PluginPrivate() {
        this->name = "cuteinputmethod" ;
        this->languages << "en" << "zh" << "en_GB" << "en_US" << "zh_CN" ;
        this->supportedStates << MInputMethod::Hardware ;
        this->supportedStates << MInputMethod::OnScreen ;
        this->settings = 0 ;
    }
    ~PluginPrivate() {
        if ( this->settings )
            delete this->settings ;
    }
} ;

Plugin::Plugin() : d_ptr( new PluginPrivate ) {
    qmlRegisterUncreatableType<inputmethod::InputMethod> ( "me.inputmethod", 1, 0, "InputMethod", "inputmethod" ) ;
    qmlRegisterUncreatableType<toolbar::Data> ( "me.inputmethod.toolbar", 1, 0, "ToolbarData", "toolbardata" ) ;
    qmlRegisterUncreatableType<toolbar::Item> ( "me.inputmethod.toolbar", 1, 0, "ToolbarItem", "toolbaritem" ) ;
}

Plugin::~Plugin() {
    delete this->d_ptr ;
}

QString Plugin::name() const {
    Q_D( const Plugin ) ;
    return d->name ;
}

QStringList Plugin::languages() const {
    Q_D( const Plugin ) ;
    return d->languages ;
}

MAbstractInputMethod* Plugin::createInputMethod( MAbstractInputMethodHost *host, QWidget *mainWindow ) {
    return new inputmethod::InputMethod( host, mainWindow ) ;
}

MAbstractInputMethodSettings* Plugin::createInputMethodSettings() {
    Q_D( Plugin ) ;
    if ( !d->settings )
        d->settings = new settings::Settings ;
    return d->settings ;
}

QSet<MInputMethod::HandlerState> Plugin::supportedStates() const {
    Q_D( const Plugin ) ;
    return d->supportedStates ;
}

}

Q_EXPORT_PLUGIN2( inputmethod, plugin::Plugin ) 
