#include <QApplication>
#include <QDBusConnection>
#include <QDeclarativeContext>
#include <QUrl>
#include <QDesktopWidget>

#include <QDebug>

#include "host.h"
#include "view.h"
#include "adaptor.h"
#include "../engine/engine.h"

int main( int argc, char** argv ) {
    QApplication app( argc, argv ) ;
    app.setInputContext( NULL ) ;

    host::Host* host = new host::Host() ;

    view::View* view = new view::View() ;
    host->setView( view ) ;

    QDesktopWidget* desktop = QApplication::desktop() ;
    view->setGeometry( desktop->geometry() ) ;
    view->move( 0, 25 ) ;
    view->displayOffsetY = 25 ;

    view->rootContext()->setContextProperty( "host", host ) ;
    view->rootContext()->setContextProperty( "view", host->view ) ;
    view->rootContext()->setContextProperty( "engine", host->engine ) ;

    view->setSource( QUrl("view/root.qml") ) ;
    //view->setSource( QUrl("qml/keyboard.qml") ) ;

    QDBusConnection::sessionBus().registerService( "me.inputmethod.host" ) ;
    QDBusConnection::sessionBus().registerObject( "/host", host ) ;

    QDBusConnection::sessionBus().connect( "", "", "inputmethod.context", "sendMessage", host->adaptor, SLOT(receiveMessage( const QString& )) ) ;
    QDBusConnection::sessionBus().connect( "", "", "inputmethod.context", "requestSoftwareInputPanel", host->adaptor, SLOT(show()) ) ;
    QDBusConnection::sessionBus().connect( "", "", "inputmethod.context", "closeSoftwareInputPanel", host->adaptor, SLOT(hide()) ) ;
    QDBusConnection::sessionBus().connect( "", "", "inputmethod.context", "focusIn", host->adaptor, SLOT(show()) ) ;
    QDBusConnection::sessionBus().connect( "", "", "inputmethod.context", "focusOut", host->adaptor, SLOT(hide()) ) ;
    QDBusConnection::sessionBus().connect( "", "", "inputmethod.context", "cursorRectUpdate", host->adaptor, SIGNAL(cursorRectUpdate( int, int, int, int )) ) ;

    QObject::connect( host->adaptor, SIGNAL(cursorRectUpdate( int, int, int, int )), view, SLOT(cursorRectUpdate( int, int, int, int )) ) ;

    return app.exec() ;
}
