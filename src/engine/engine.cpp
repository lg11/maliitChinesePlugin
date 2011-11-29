#include "engine.h"
#include "worker.h"
#include "puncmap.h"

#include <QList>
#include <QString>
#include <QHash>

//#include <QDebug>

namespace engine {

enum FunctionKey {
    CANDIDATE_SPACE ,
    CANDIDATE_1 ,
    CANDIDATE_2 ,
    CANDIDATE_3 ,
    CANDIDATE_4 ,
    CANDIDATE_5 ,
    NEXT_PAGE ,
    PREV_PAGE ,
    SWITCH_ACTIVE ,
    BACKSPACE ,
    CANDIDATE_RETURN
} ;

class EnginePrivate {
public :
    Worker* worker ;
    int pageLength ;
    bool active ;
    bool working ;
    int functionKey[16] ;
    PuncMap* puncMap ;
    QHash<QString, int> hash ;
    EnginePrivate() :
        worker( new Worker() ) , 
        pageLength( 5 ) ,
        active( false ) ,
        working( false ) ,
        puncMap( new PuncMap() ) ,
        hash()
    {
        //qDebug() << "init engine" ;
        this->hash.insert( "CANDIDATE_SPACE", CANDIDATE_SPACE ) ;
        this->hash.insert( "CANDIDATE_1", CANDIDATE_1 ) ;
        this->hash.insert( "CANDIDATE_2", CANDIDATE_2 ) ;
        this->hash.insert( "CANDIDATE_3", CANDIDATE_3 ) ;
        this->hash.insert( "CANDIDATE_4", CANDIDATE_4 ) ;
        this->hash.insert( "CANDIDATE_5", CANDIDATE_5 ) ;
        this->hash.insert( "NEXT_PAGE", NEXT_PAGE ) ;
        this->hash.insert( "PREV_PAGE", PREV_PAGE ) ;
        this->hash.insert( "SWITCH_ACTIVE", SWITCH_ACTIVE ) ;
        this->hash.insert( "BACKSPACE", BACKSPACE ) ;
        this->hash.insert( "CANDIDATE_RETURN", CANDIDATE_RETURN ) ;

        this->functionKey[CANDIDATE_SPACE] = Qt::Key_Space ;
        this->functionKey[CANDIDATE_1] = Qt::Key_1 ;
        this->functionKey[CANDIDATE_2] = Qt::Key_2 ;
        this->functionKey[CANDIDATE_3] = Qt::Key_3 ;
        this->functionKey[CANDIDATE_4] = Qt::Key_4 ;
        this->functionKey[CANDIDATE_5] = Qt::Key_5 ;
        this->functionKey[NEXT_PAGE] = Qt::Key_BracketRight ;
        this->functionKey[PREV_PAGE] = Qt::Key_BracketLeft ;
        this->functionKey[SWITCH_ACTIVE] = Qt::Key_Control ;
        this->functionKey[BACKSPACE] = Qt::Key_Backspace ;
        this->functionKey[CANDIDATE_RETURN] = Qt::Key_Return ;

        this->worker->setKeyboardLayout( Worker::FullKeyboardLayout ) ;
    }
    ~EnginePrivate() {
        delete this->worker ;
        delete this->puncMap ;
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

bool Engine::getActive() const {
    Q_D( const Engine ) ;
    return d->active ;
}

void Engine::setActive( bool active ) {
    Q_D( Engine ) ;
    if ( d->active != active ) {
        d->active = active ;
        emit this->activeChanged( d->active ) ;
    }
}

bool Engine::getWorking() const {
    Q_D( const Engine ) ;
    return d->working ;
}

void Engine::setWorking( bool working ) {
    Q_D( Engine ) ;
    if ( d->working != working ) {
        d->working = working ;
        emit this->workingChanged( d->working ) ;
    }
}

void Engine::load( const QString& path ) {
    Q_D( Engine ) ;
    d->worker->load( path ) ; 
}

void Engine::setFunctionKey( const QString& function, int key ) {
    Q_D( Engine ) ;
    if ( d->hash.contains( function ) ) {
        int index = d->hash.value( function ) ;
        d->functionKey[index] = key ;
    }
}

bool Engine::selectCandidate( int index ) {
    Q_D( Engine ) ;
    bool flag = d->worker->select( index ) ;
    if ( d->worker->getSelectedWordLength() > 0 ) {
        if ( !d->worker->updateCandidate( 0 ) ) {
            emit this->commit( d->worker->getSelectedWord() ) ;
            d->worker->commit() ;
        }
    }
    return flag ;
}

bool Engine::processKeyEvent( QEvent::Type type, int keycode, Qt::KeyboardModifiers modifiers, const QString& text, bool autoRepeat, int count ) {
    Q_UNUSED( type ) ;
    Q_UNUSED( modifiers ) ;
    Q_UNUSED( text ) ;
    Q_UNUSED( autoRepeat ) ;
    Q_UNUSED( count ) ;
    
    Q_D( Engine ) ;

    bool flag = false ;

    //qDebug() << "processs start" ;
    
    if ( keycode == d->functionKey[SWITCH_ACTIVE] ) {
        if ( !d->working )
            this->setActive( !d->active ) ;
    }
    else if ( d->active ) {
        if ( keycode >= Qt::Key_A && keycode <= Qt::Key_Z ) {
            QChar code = keycode + 'a' - 'A' ;
            flag = d->worker->appendCode( code ) ;
            this->setWorking( true ) ;
        }
        else if ( keycode == d->functionKey[BACKSPACE] ) {
            if ( d->worker->getCodeLength() > 0 ) 
                flag = d->worker->popCode() ;
            else if ( d->worker->getSelectedWordLength() > 0 )
                flag = d->worker->deselect() ;
        }
        else if ( keycode == d->functionKey[CANDIDATE_SPACE] || keycode == d->functionKey[CANDIDATE_1] ) 
            flag = this->selectCandidate( 0 ) ;
        else if ( keycode == d->functionKey[CANDIDATE_2] ) 
            flag = this->selectCandidate( 1 ) ;
        else if ( keycode == d->functionKey[CANDIDATE_3] ) 
            flag = this->selectCandidate( 2 ) ;
        else if ( keycode == d->functionKey[CANDIDATE_4] ) 
            flag = this->selectCandidate( 3 ) ;
        else if ( keycode == d->functionKey[CANDIDATE_5] ) 
            flag = this->selectCandidate( 4 ) ;
        else if ( keycode == d->functionKey[NEXT_PAGE] ) 
            flag = d->worker->nextPage( d->pageLength ) ;
        else if ( keycode == d->functionKey[PREV_PAGE] ) 
            flag = d->worker->prevPage( d->pageLength ) ;
        else if ( keycode == d->functionKey[CANDIDATE_RETURN] ) {
            if ( d->worker->getCodeLength() > 0 ) {
                flag = true ;
                emit this->commit( d->worker->getCode() ) ;
                d->worker->reset() ;
            }
        }
    }

    if ( flag ) {
        emit this->updated() ;
        if ( d->worker->getSelectedWordLength() <= 0 && d->worker->getCodeLength() <= 0 )
            this->setWorking( false ) ;
    }

    return flag || d->working ;
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

const QString* Engine::convertPunc( const QString& src ) {
    Q_D( Engine ) ;
    return d->puncMap->remap( src[0] ) ;
}

void Engine::remapPunc( const QString& src, const QString& dest ) {
    Q_D( Engine ) ;
    d->puncMap->setRemap( src[0], dest ) ;
}

void Engine::unramapPunc( const QString& src ) {
    Q_D( Engine ) ;
    d->puncMap->unsetRemap( src[0] ) ;
}


}
