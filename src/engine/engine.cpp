#include "engine.h"
#include "worker.h"

#include <QList>
#include <QString>

namespace engine {

class EnginePrivate {
public :
    Worker* worker ;
    int pageLength ;
    EnginePrivate() :
        worker( new Worker() ), 
        pageLength( 5 )
    {
        this->worker->setKeyboardLayout( Worker::FullKeyboardLayout ) ;
    }
    ~EnginePrivate() {
        delete this->worker ;
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

void Engine::appendCode( QChar code ) {
    Q_D( Engine ) ;
    d->worker->appendCode( code ) ; 
    emit this->updated() ;
}

void Engine::appendCode( const QString& code ) {
    if ( code.length() > 0 ) 
        this->appendCode( code[0] ) ;
}

void Engine::appendCode( int keycode ) {
    QChar code = keycode + 'a' - 'A' ;
    this->appendCode( code ) ; 
}

void Engine::popCode() {
    Q_D( Engine ) ;
    d->worker->popCode() ;
    emit this->updated() ;
}

void Engine::reset() {
    Q_D( Engine ) ;
    d->worker->reset() ;
    emit this->updated() ;
}

void Engine::select( int index ) {
    Q_D( Engine ) ;
    d->worker->select( index ) ;
    emit this->updated() ;
}

void Engine::deselect() {
    Q_D( Engine ) ;
    d->worker->deselect() ;
    emit this->updated() ;
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
