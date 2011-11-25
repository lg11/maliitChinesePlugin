#include "inputmethod.h"
#include "inputmethodview.h"
#include "engine.h"

#include <QRect>
#include <QRegion>
#include <QKeyEvent>

#include <mabstractinputmethodhost.h>
//#include <mtoolbardata.h>
//#include <mtoolbaritem.h>
//#include <mtoolbarlayout.h>

#include <QDebug>

namespace inputmethod {

class InputMethodPrivate {
public :
    //Q_DECLARE_PUBLIC( InputMethod ) ;
    InputMethodView* const view ;
    QRect inputMethodArea ;
    int appOrientation ;
    QRect cursorRect ;
    QList<MInputMethod::PreeditTextFormat> preeditFormat ;
    engine::Engine* engine ;
    //toolbar::Data* toolbarData ;
    QString debugString ;
    
    InputMethodPrivate( QWidget* mainWindow ) :
        view( new InputMethodView( mainWindow ) ) ,
        inputMethodArea() ,
        appOrientation( 0 ) ,
        cursorRect() ,
        preeditFormat() ,
        engine( new engine::Engine ) ,
        //toolbarData( new toolbar::Data() ) ,
        debugString()
    {
        //ok = connect(imToolbar, SIGNAL(copyPasteRequest(CopyPasteState)),
                     //this, SLOT(sendCopyPaste(CopyPasteState)));
        //Q_ASSERT(ok);
        //ok = connect(imToolbar, SIGNAL(sendKeyEventRequest(const QKeyEvent &)),
                     //this, SLOT(sendKeyEvent(const QKeyEvent &)));
        //Q_ASSERT(ok);
        //ok = connect(imToolbar, SIGNAL(sendStringRequest(const QString &)),
                     //this, SLOT(sendStringFromToolbar(const QString &)));
        //Q_ASSERT(ok);
        //ok = connect(imToolbar, SIGNAL(copyPasteClicked(CopyPasteState)),
                     //this, SLOT(sendCopyPaste(CopyPasteState)));
        //Q_ASSERT(ok);
        //ok = connect(imToolbar, SIGNAL(closeKeyboardRequest()),
                     //this, SLOT(userHide()));
        //Q_ASSERT(ok);

        this->preeditFormat.append( MInputMethod::PreeditTextFormat( 0, 0, MInputMethod::PreeditDefault ) ) ;
        this->preeditFormat.append( MInputMethod::PreeditTextFormat( 0, 0, MInputMethod::PreeditNoCandidates ) ) ;
        //this->engine->rootContext()->setContextProperty( "toolbarData", this->toolbarData ) ;
    }

    ~InputMethodPrivate() {
        delete this->view ;
        //delete this->toolbarData ;
    }
} ;



InputMethod::InputMethod( MAbstractInputMethodHost *host, QWidget *mainWindow ) :
    MAbstractInputMethod( host, mainWindow ),
    d_ptr( new InputMethodPrivate( mainWindow ) )
{
    qDebug() << "inputmethod" << "construct" ;
    Q_D( InputMethod ) ;
    d->view->setInputMethod( this ) ;
    d->view->setEngine( d->engine ) ;
    d->view->load( "/opt/linputmehtod/qml/main.qml" ) ;
    //qDebug() << d->engine ;

    QWidget* viewport = d->view->viewport() ;

    if ( viewport->nativeParentWidget() )
            viewport = viewport->nativeParentWidget() ;

    const QRect& rect( d->view->screenRect( viewport ) ) ;
    d->view->resize( rect.size() ) ;
    d->view->setSceneRect( rect ) ;
    d->view->show() ;
    d->view->setFrameShape( QFrame::NoFrame ) ;
    d->view->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff ) ;
    d->view->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff ) ;
}

InputMethod::~InputMethod() { delete this->d_ptr ; }

void InputMethod::show() {
    qDebug() << "inputmethod" << "show" ;
    Q_D( InputMethod ) ;
    d->view->showContent() ;

    const QRegion region( d->inputMethodArea ) ;
    this->inputMethodHost()->setScreenRegion( region ) ;
    this->inputMethodHost()->setInputMethodArea( region ) ;
}

void InputMethod::hide() {
    qDebug() << "inputmethod" << "hide" ;
    Q_D( InputMethod ) ;
    d->view->hideContent() ;

    const QRegion region ;
    this->inputMethodHost()->setScreenRegion( region ) ;
    this->inputMethodHost()->setInputMethodArea( region ) ;
}

void InputMethod::setPreedit( const QString &preeditString, int cursorPos ) {
    qDebug() << "inputmethod" << "setPreedit" ;
    Q_UNUSED( preeditString )
    Q_UNUSED( cursorPos )
}

void InputMethod::update() {
    //qDebug() << "inputmethod" << "update" ;
    Q_D( InputMethod ) ;
    bool flag ;
    const QRect cursorRect( this->inputMethodHost()->cursorRectangle( flag ) ) ;
    if ( flag && d->cursorRect != cursorRect ) {
        d->cursorRect = cursorRect ;
        emit this->cursorRectChanged( d->cursorRect ) ;
    }
}

void InputMethod::reset() {
    qDebug() << "inputmethod" << "reset" ;
}

void InputMethod::handleMouseClickOnPreedit( const QPoint &pos, const QRect &preeditRect ) {
    qDebug() << "inputmethod" << "handleMouseClickOnPreedit" ;
    Q_UNUSED( pos )
    Q_UNUSED( preeditRect )
}

void InputMethod::handleFocusChange( bool focusIn ) {
    qDebug() << "inputmethod" << "handleFocusChange" ;
    if ( focusIn ) {
        this->inputMethodHost()->setRedirectKeys( true ) ;
    }
    //else
        //this->hide() ;
}

void InputMethod::handleVisualizationPriorityChange( bool priority ) {
    qDebug() << "inputmethod" << "handleVisualizationPriorityChange" ;
    Q_UNUSED( priority ) 
}

void InputMethod::handleAppOrientationAboutToChange( int angle ) {
    qDebug() << "inputmethod" << "handleAppOrientationAboutToChange" ;
    Q_UNUSED( angle ) 
}

void InputMethod::handleAppOrientationChanged( int angle) {
    qDebug() << "inputmethod" << "handleAppOrientationChanged" ;
    Q_D( InputMethod ) ;
    
    if ( d->appOrientation != angle ) {
        d->appOrientation = angle ;
        //d->toolbarData->setOrientation( angle ) ;
        emit this->appOrientationChanged( d->appOrientation ) ;
    }
}
void InputMethod::setToolbar( QSharedPointer<const MToolbarData> toolbar ) {
    qDebug() << "inputmethod" << "setToolbar" ;
    //Q_D( InputMethod ) ;
    if ( toolbar ) {
        //d->toolbarData->set( toolbar ) ;
    }
}

void InputMethod::processKeyEvent( QEvent::Type keyType, Qt::Key keyCode, Qt::KeyboardModifiers modifiers, const QString& text, bool autoRepeat, int count, quint32 nativeScanCode, quint32 nativeModifiers, unsigned long time) {
    qDebug() << "inputmethod" << "processKeyEvent" << keyCode ;
    Q_D( InputMethod ) ;
    Q_UNUSED( nativeScanCode )
    Q_UNUSED( nativeModifiers )
    Q_UNUSED( time )

    bool flag = false ;
    if ( d->engine ) {
        flag = d->engine->processKeyEvent( keyType, keyCode, modifiers, text, autoRepeat, count ) ;
    }
    if ( !flag ) {
        QKeyEvent event( keyType, keyCode, modifiers, text, autoRepeat, count ) ;
        this->inputMethodHost()->sendKeyEvent( event ) ;
    }
}
void InputMethod::setState( const QSet<MInputMethod::HandlerState> &state ) {
    qDebug() << "inputmethod" << "setState" ;
    Q_UNUSED( state )
}

void InputMethod::handleClientChange() {
    qDebug() << "inputmethod" << "handleClientChange" ;
}

void InputMethod::switchContext( MInputMethod::SwitchDirection direction, bool enableInAnimation ) {
    qDebug() << "inputmethod" << "switchContext" ;
    Q_UNUSED( direction )
    Q_UNUSED( enableInAnimation )
}

QList<InputMethod::MInputMethodSubView> InputMethod::subViews( MInputMethod::HandlerState state ) const {
    qDebug() << "inputmethod" << "subViews" ;

    QList<MAbstractInputMethod::MInputMethodSubView> list ;
    if ( state == MInputMethod::OnScreen ) {
        MAbstractInputMethod::MInputMethodSubView subView ;
        subView.subViewId = 250 ;
        subView.subViewTitle = "linputmethod" ;
        list.append(subView) ;
    }

    return list;
}

void InputMethod::setActiveSubView( const QString &subViewId, MInputMethod::HandlerState state ) {
    qDebug() << "inputmethod" << "setActiveSubView" ;
    Q_UNUSED( subViewId )
    Q_UNUSED( state )
}

QString InputMethod::activeSubView( MInputMethod::HandlerState state ) const {
    qDebug() << "inputmethod" << "activeSubView" ;
    Q_UNUSED( state )
    return "" ;
}

void InputMethod::showLanguageNotification() {
    qDebug() << "inputmethod" << "showLanguageNotification" ;
}

void InputMethod::setKeyOverrides( const QMap<QString, QSharedPointer<MKeyOverride> > &overrides ) {
    qDebug() << "inputmethod" << "setKeyOverrides" ;
    Q_UNUSED( overrides )
}

bool InputMethod::imExtensionEvent( MImExtensionEvent *event) {
    qDebug() << "inputmethod" << "imExtensionEvent" ;
    Q_UNUSED( event )
    return false ;
}

int InputMethod::screenWidth() const {
    Q_D( const InputMethod ) ;
    return d->view->screenRect().width() ;
}

int InputMethod::screenHeight() const {
    Q_D( const InputMethod ) ;
    return d->view->screenRect().height() ;
}

int InputMethod::appOrientation() const {
    Q_D( const InputMethod ) ;
    return d->appOrientation ;
}

const QRect& InputMethod::cursorRect() const {
    Q_D( const InputMethod ) ;
    return d->cursorRect ;
}

const QString& InputMethod::debugString() const {
    Q_D( const InputMethod ) ;
    return d->debugString ;
}

void InputMethod::setScreenRegion( const QRect &area ) {
    QRegion region( area ) ;
    this->inputMethodHost()->setScreenRegion( region ) ;
}

void InputMethod::setInputMethodArea( const QRect &area ) {
    Q_D( InputMethod ) ;
    if ( d->inputMethodArea != area ) {
        d->inputMethodArea = area ;
        QRegion region( area ) ;
        this->inputMethodHost()->setInputMethodArea( region ) ;
    }
}

//void InputMethod::sendKeyEvent( const QString& text ) {}

void InputMethod::sendPreedit( const QString& black, const QString& red ) {
    Q_D( InputMethod ) ;
    if ( red.isEmpty() ) {
        if ( !black.isEmpty() ) {
            d->preeditFormat[0].start = 0 ;
            d->preeditFormat[0].length = black.length() ;
            d->preeditFormat[1].start = black.length() ;
            d->preeditFormat[1].length = 0 ;
            this->inputMethodHost()->sendPreeditString( black, d->preeditFormat ) ;
        }
        else {
            d->preeditFormat[0].start = 0 ;
            d->preeditFormat[0].length = 0 ;
            d->preeditFormat[1].start = 0 ;
            d->preeditFormat[1].length = 0 ;
            this->inputMethodHost()->sendPreeditString( "", d->preeditFormat ) ;
        }
    }
    else if ( black.isEmpty() ) {
        d->preeditFormat[0].start = 0 ;
        d->preeditFormat[0].length = 0 ;
        d->preeditFormat[1].start = 0 ;
        d->preeditFormat[1].length = red.length() ;
        this->inputMethodHost()->sendPreeditString( red, d->preeditFormat ) ;
    }
    else {
        d->preeditFormat[0].start = 0 ;
        d->preeditFormat[0].length = black.length() ;
        d->preeditFormat[1].start = black.length() ;
        d->preeditFormat[1].length = red.length()  ;
        QString str( black ) ;
        str.append( red ) ;
        this->inputMethodHost()->sendPreeditString( str, d->preeditFormat ) ;
    }
}

void InputMethod::sendCommit( const QString& text ) {
    if ( text == "\b" ) {
        QKeyEvent event( QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier ) ;
        this->inputMethodHost()->sendKeyEvent( event ) ;
    }
    else if ( text == "\r\n" ) {
        QKeyEvent event( QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier );
        this->inputMethodHost()->sendKeyEvent( event ) ;
    } else {
        this->inputMethodHost()->sendCommitString( text ) ;
    }
}


}
