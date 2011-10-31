#include "plugin.h"
#include "inputmethod.h"
#include "settings.h"

namespace plugin {

class PluginPrivate {
public :
    QString name ;
    QStringList languages ;
    QSet<MInputMethod::HandlerState> supportedStates ;
    PluginPrivate() {
        this->name = "cuteinputmethod" ;
        this->languages << "en" << "zh" << "en_GB" << "en_US" << "zh_CN" ;
        this->supportedStates << MInputMethod::Hardware ;
        this->supportedStates << MInputMethod::OnScreen ;
    }
    ~PluginPrivate() {}
} ;

Plugin::Plugin() : d_ptr( new PluginPrivate ) {
    this->settings = 0 ;
    //qmlRegisterUncreatableType<inputmethod::InputMethod> ( "me.inputmethod", 1, 0, "InputMethod", "inputmethod" ) ;
}

Plugin::~Plugin() {
    if ( this->settings )
        delete this->settings ;
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
    if ( !this->settings )
        this->settings = new settings::Settings ;
    return this->settings ;
}

QSet<MInputMethod::HandlerState> Plugin::supportedStates() const {
    Q_D( const Plugin ) ;
    return d->supportedStates ;
}

}

Q_EXPORT_PLUGIN2( inputmethod, plugin::Plugin ) 
