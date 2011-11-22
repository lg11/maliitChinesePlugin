#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include "worker.h"

#include <QDebug>


namespace engine {

class Engine : public QObject {
    Q_OBJECT
public :
    Worker* worker ;
    int pageLength ;

    Engine( QObject* parent = 0 ) : QObject( parent), worker( new Worker() ), pageLength( 5 ) {
        this->worker->setKeyboardLayout( Worker::FullKeyboardLayout ) ;
    }

    ~Engine() { delete this->worker ; }

    void load( const QString& path ) { this->worker->load( path ) ; }

    void appendCode( QChar code ) {
        this->worker->appendCode( code ) ; 
    }

    void appendCode( const QString& code ) {
        if ( code.length() > 0 ) 
            this->appendCode( code[0] ) ;
    }

    void popCode() { this->worker->popCode() ; }

    void reset() { this->worker->reset() ; }

    void select( int index ) { this->worker->select( index ) ; }

    void deselect() { this->worker->deselect() ; }

    QString getCandidateString() {
        qDebug() << "getCand" ;
        QString str ;
        bool flag ;
        flag = this->worker->updateCandidate( 0 ) ;
        if ( flag || this->worker->getSelectedWordLength() > 0 )
            str.append( this->worker->getSelectedWord() ) ;
        str.append( QChar(',') ) ;
        if ( flag )
            str.append( this->worker->getPreeditCode() ) ;
        str.append( QChar(',') ) ;
        if ( flag || this->worker->getInvalidCodeLength() > 0 )
            str.append( this->worker->getInvalidCode() ) ;
        str.append( QChar(',') ) ;
        if ( flag )
            str.append( this->worker->getWord() ) ;
        for ( int i = 1 ; i < this->pageLength ; i++ ) {
            str.append( QChar(',') ) ;
            flag = this->worker->updateCandidate( i ) ;
            if ( flag )
                str.append( this->worker->getWord() ) ;
        }

        qDebug() << str ;
        return str ;
    }

} ;

}

#endif // ENGINE_ENGINE_H
