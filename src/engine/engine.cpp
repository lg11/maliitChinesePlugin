#include "engine.h"
#include "worker.h"

namespace engine {

class EnginePrivate {
public :
    Worker* worker ;
    int pageLength ;
    EnginePrivate() : worker( new Worker() ), pageLength( 5 ) {
        this->worker->setKeyboardLayout( Worker::FullKeyboardLayout ) ;
    }
    ~EnginePrivate() { delete this->worker ; }
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
}

void Engine::appendCode( const QString& code ) {
    if ( code.length() > 0 ) 
        this->appendCode( code[0] ) ;
}

void Engine::popCode() {
    Q_D( Engine ) ;
    d->worker->popCode() ;
}

void Engine::reset() {
    Q_D( Engine ) ;
    d->worker->reset() ;
}

void Engine::select( int index ) {
    Q_D( Engine ) ;
    d->worker->select( index ) ;
}

void Engine::deselect() {
    Q_D( Engine ) ;
    d->worker->deselect() ;
}

QString Engine::getCandidateString() {
    Q_D( Engine ) ;
    qDebug() << "getCand" ;
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

    qDebug() << str ;
    return str ;
}

}
