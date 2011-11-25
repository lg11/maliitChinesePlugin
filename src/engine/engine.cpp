#include "engine.h"
#include "worker.h"
#include "keyfilter.h"

#include <QList>
#include <QString>

//#include <QDebug>

namespace engine {

class EnginePrivate {
public :
    Worker* worker ;
    int pageLength ;
    KeyFilter* keyFilter ;
    EnginePrivate() :
        worker( new Worker() ), 
        pageLength( 5 ) ,
        keyFilter( new KeyFilter() ) 
    {
        this->worker->setKeyboardLayout( Worker::FullKeyboardLayout ) ;
    }
    ~EnginePrivate() {
        delete this->worker ;
        delete this->keyFilter ;
    }
} ;

Engine::Engine( QObject* parent ) :
    QObject( parent),
    d_ptr( new EnginePrivate() )
{
}

Engine::~Engine() {
    delete this->d_ptr ;
}

void Engine::load( const QString& path ) {
    Q_D( Engine ) ;
    d->worker->load( path ) ; 
}

bool Engine::processKeyEvent( QEvent::Type type, Qt::Key keycode, Qt::KeyboardModifiers modifiers, const QString& text, bool autoRepeat, int count ) {
    Q_D( Engine ) ;
    bool flag = d->keyFilter->filter( type, keycode, modifiers, text, autoRepeat, count ) ;
    if ( !flag ) {
        if ( keycode >= Qt::Key_A && keycode <= Qt::Key_Z ) {
            QChar code = keycode + 'a' - 'A' ;
            flag = d->worker->appendCode( code ) ;
        }
        else if ( keycode == Qt::Key_Backspace ) {
            if ( d->worker->getCodeLength() > 0 )
                flag = d->worker->popCode() ;
            else if ( d->worker->getSelectedWordLength() > 0 )
                flag = d->worker->deselect() ;
        }
        else if ( keycode == Qt::Key_Space ) {
            flag = d->worker->select( 0 ) ;
            if ( d->worker->getSelectedWordLength() > 0 ) {
                if ( !d->worker->updateCandidate( 0 ) ) {
                    emit this->commit( d->worker->getSelectedWord() ) ;
                    d->worker->commit() ;
                }
            }
        }
        else if ( keycode >= Qt::Key_1 && keycode <= Qt::Key_5 ) {
            flag = d->worker->select( keycode - Qt::Key_1 ) ;
            if ( d->worker->getSelectedWordLength() > 0 ) {
                if ( !d->worker->updateCandidate( 0 ) ) {
                    emit this->commit( d->worker->getSelectedWord() ) ;
                    d->worker->commit() ;
                }
            }
        }
        if ( flag ) 
            emit this->updated() ;
    }

    return flag || d->worker->getSelectedWordLength() > 0 || d->worker->getCodeLength() > 0 ;
}

QString Engine::getCandidateString() {
    Q_D( Engine ) ;
    QString str ;

    bool flag ;
    flag = d->worker->updateCandidate( 0 ) ;
    
    if ( flag || d->worker->getSelectedWordLength() > 0 )
        str.append( d->worker->getSelectedWord() ) ;
    str.append( QChar(',') ) ;
    if ( flag )
        str.append( d->worker->getPreeditCode() ) ;
    str.append( QChar(',') ) ;
    if ( flag || d->worker->getInvalidCodeLength() > 0 )
        str.append( d->worker->getInvalidCode() ) ;
    str.append( QChar(',') ) ;
    if ( flag )
        str.append( d->worker->getWord() ) ;
    for ( int i = 1 ; i < d->pageLength ; i++ ) {
        str.append( QChar(',') ) ;
        flag = d->worker->updateCandidate( i ) ;
        if ( flag )
            str.append( d->worker->getWord() ) ;
    }

    //qDebug() << str ;
    return str ;
}

}
