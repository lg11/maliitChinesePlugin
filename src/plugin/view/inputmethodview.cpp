#include "inputmethodview.h"
#include "engine.h"

#include <QGraphicsScene>
#include <QDeclarativeEngine>
#include <QGraphicsObject>
#include <QDeclarativeComponent>
#include <QDeclarativeContext>

#include <QApplication>
#include <QDesktopWidget>

namespace inputmethod {

const QRect& display_rect( QWidget* widget = 0 ) {
    static const QRect rect( widget ? QApplication::desktop()->screenGeometry( widget ) : QApplication::desktop()->screenGeometry() ) ;
    return rect ;
}

class InputMethodViewPrivate {
public :
    QGraphicsScene* scene ;
    QDeclarativeEngine* engine ;
    QGraphicsObject* content ;
    QDeclarativeComponent* component ;
    InputMethodViewPrivate() :
        scene( NULL ) ,
        engine( new QDeclarativeEngine() ) ,
        content( NULL ) ,
        component( NULL ) 
    {
    }
    ~InputMethodViewPrivate() {
        if ( this->content )
            delete this->content ;
        if ( this->component )
            delete this->component ;
        delete this->scene ;
        delete this->engine ;
    }
} ;

InputMethodView::InputMethodView( QWidget* mainWindow ) :
    MImGraphicsView( new QGraphicsScene( display_rect(), 0 ), mainWindow ) ,
    d_ptr( new InputMethodViewPrivate() )
{
    Q_D( InputMethodView ) ;
    d->scene = this->scene() ;
}

InputMethodView::~InputMethodView() {
    delete this->d_ptr ;
}

void InputMethodView::showContent() {
    Q_D( InputMethodView ) ;
    if ( d->content ) {
        d->content->show() ;
    }
}

void InputMethodView::hideContent() {
    Q_D( InputMethodView ) ;
    if ( d->content ) {
        d->content->hide() ;
    }
}

void InputMethodView::load( const QString& path ) {
    Q_D( InputMethodView ) ;
    d->component = new QDeclarativeComponent( d->engine, QUrl( path ) ) ;
    d->content = qobject_cast<QGraphicsObject*>( d->component->create() ) ;
    d->scene->addItem( d->content ) ;
}

void InputMethodView::setInputMethod( MAbstractInputMethod* inputmethod ) {
    Q_D( InputMethodView ) ;
    d->engine->rootContext()->setContextProperty( "inputmethod", inputmethod ) ;
}

void InputMethodView::setEngine( engine::Engine* engine ) {
    Q_D( InputMethodView ) ;
    d->engine->rootContext()->setContextProperty( "engine", engine ) ;
}

const QRect& InputMethodView::screenRect( QWidget* widget ) {
    return display_rect( widget ) ;
}

}
