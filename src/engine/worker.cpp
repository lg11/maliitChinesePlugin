#include "worker.h"
#include "t9.h"
#include "pinyin.h"

#include <QStringList>
#include <QSet>

//#include <QDebug>

namespace engine {

inline void append_selected( SelectedPair* pair, const QString* key, const QString* preedit, const QString* word, qreal freq ) {
    if ( !pair->first.first.isEmpty() ) {
        pair->first.first.append( QChar('\'') ) ;
        pair->first.second.append( QChar('\'') ) ;
    }
    pair->first.first.append( *key ) ;
    pair->first.second.append( *preedit ) ;
    pair->second.first.append( *word ) ;
    int count = key->count( QChar('\'') ) ;
    for ( int i = 0 ; i < count ; i ++ ) ;
        pair->second.second.append( -1 ) ;
    pair->second.second.append( freq ) ;
}

inline void clear_selected( SelectedPair* pair ) {
    pair->first.first.clear() ;
    pair->first.second.clear() ;
    pair->second.first.clear() ;
    pair->second.second.clear() ;
}

inline void pop_selected( SelectedPair* pair, QString* code ) {
    if ( pair->second.first.length() > 1 ) {
        int index ;
        int length ;
        
        //qDebug() << *pair ;
        index = pair->first.first.lastIndexOf( QChar('\'') ) ;
        length = pair->first.first.length() ;
        pair->first.first.chop( length - index ) ;

        index = pair->first.second.lastIndexOf( QChar('\'') ) ;
        length = pair->first.second.length() ;
        *code = pair->first.second.right( length - index - 1 ) ;
        pair->first.second.chop( length - index ) ;

        pair->second.first.chop( 1 ) ;
        pair->second.second.removeLast() ;
    }
    else {
        *code = pair->first.second ;
        clear_selected( pair ) ;
    }
}

Worker::Worker() : 
    dict( new dict::Dictionary ) ,
    lookup( 0 ) ,
    pinyinLookup( new lookup::PinyinLookup(this->dict) ),
    t9Lookup( new lookup::T9Lookup( this->dict) ) ,
    selected( new SelectedPair ) ,
    selectedWord( &(this->selected->second.first) )
{
    //qDebug() << "init worker" ;
    this->pageStartIndex = 0 ;
    this->candidate = NULL ;
    this->keyboardLayout = UnknownKeyboardLayout ;
    //this->logFile = NULL ;
    //this->textStream = NULL ;

    //this->flushTimer.setInterval( 1200000 ) ;
    //QObject::connect( &(this->flushTimer), SIGNAL(timeout()), this, SLOT(flushLog() ) ) ;
}

Worker::~Worker() {
    delete this->pinyinLookup ;
    delete this->t9Lookup ;
    delete this->dict ;
    delete this->selected ;
    //if ( this->logFile ) {
        //delete this->textStream ;
        //this->logFile->close() ;
        //delete this->logFile ;
    //}
}

//void Worker::startLog( const QString& path ) {
    //this->logFile = new QFile( path ) ;
    //if ( this->logFile->exists() ) {
        //this->logFile->open( QIODevice::WriteOnly | QIODevice::Append ) ;
        //this->textStream = new QTextStream( this->logFile ) ;
        //this->textStream->setCodec( "utf-8" ) ;
        //this->textStream->setRealNumberNotation( QTextStream::SmartNotation ) ;
        //this->textStream->setRealNumberPrecision( 16 ) ;
        //this->flushTimer.start() ;
    //}
    //else {
        //delete this->logFile ;
        //this->logFile = NULL ;
    //}
//}

//void Worker::stopLog() {
    //if ( this->logFile ) {
        //delete this->textStream ;
        //this->logFile->close() ;
        //delete this->logFile ;
        //this->logFile = NULL ;
        //this->textStream = NULL ;
        //this->flushTimer.stop() ;
    //}
//}

//void Worker::flushLog() {
    //if ( this->logFile ) 
        //this->logFile->flush() ;
//}

void Worker::load( const QString& path ) {
    QFile file( path ) ;
    if ( file.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
        QSet<QString> newKeySet ;
        QTextStream in( &file ) ;
        in.setCodec( "utf-8" ) ;
        while( !in.atEnd() ) {
            QString line = in.readLine() ;
            QStringList list = line.split( " " ) ;
            if ( list.length() == 3 ) {
                QString key = list.at(0) ;
                QString word = list.at(1) ;
                qreal freq = list.at(2).toDouble() ;
                //qDebug() << key << word << freq ;
                if ( !this->dict->hash.contains( key ) )
                    newKeySet.insert( key ) ;
                this->dict->insert( key, word, freq ) ;
            }
        }
        foreach( const QString& key, newKeySet ) {
            if ( key.count( '\'' ) <= 0 )
                split::add_key( &(this->pinyinLookup->keySet), key ) ;
            fit::add_key( &(this->pinyinLookup->keyMap), key ) ;
            this->t9Lookup->tree.addKey( key ) ;
        }
    }
}

bool Worker::prevPage( int pageLength ) {
    bool flag = false ;
    if ( this->pageStartIndex >= pageLength ) {
        this->pageStartIndex -= pageLength ;
        if ( this->pageStartIndex < 0 )
            this->pageStartIndex = 0 ;
        flag = true ;
    }
    return flag ;
}

bool Worker::nextPage( int pageLength ) {
    bool flag = false ;
    if ( this->getCodeLength() > 0 ) {
        int pageStartIndex = this->pageStartIndex + pageLength ;
        const lookup::Candidate* candidate = this->lookup->getCandidate( pageStartIndex ) ;
        if ( candidate ) {
            this->pageStartIndex = pageStartIndex ;
            flag = true ;
        }
    }
    return flag ;
}

int Worker::getCodeLength() const {
    return this->lookup->code.length() ;
}

int Worker::getPreeditCodeLength() const {
    if ( this->candidate ) {
        const QString* preedit = lookup::get_preedit( this->candidate ) ;
        return preedit->length() - preedit->count( '\'' ) ;
    }
    return 0 ;
}

int Worker::getInvalidCodeLength() const { return this->getCodeLength() - this->getPreeditCodeLength() ; }

int Worker::getSelectedWordLength() const { return this->selectedWord->length() ; }

bool Worker::updateCandidate( int index ) {
    if ( this->lookup->code.isEmpty() )
        this->candidate = NULL ;
    else 
        this->candidate = this->lookup->getCandidate( pageStartIndex + index ) ;
    return this->candidate ;
    //if ( this->candidate ) 
        //qDebug() << *(lookup::get_key( this->candidate )) << *(lookup::get_preedit( this->candidate )) << *(lookup::get_word( this->candidate )) << lookup::get_freq( this->candidate ) ;
}


QString Worker::getCode() const {
    return this->lookup->code ;
}

QString Worker::getWord() const {
    if ( this->candidate ) 
        return *(lookup::get_word( this->candidate )) ;
    else 
        return "" ;
}

QString Worker::getPreeditCode() const {
    if ( this->candidate ) 
        return *(lookup::get_preedit( this->candidate )) ;
    else
        return "" ;
}

QString Worker::getInvalidCode() const {
    if ( this->lookup->code.isEmpty() )
        return "" ;
    else
        return this->lookup->code.right( this->getInvalidCodeLength() ) ;
}

QString Worker::getSelectedWord() const {
    return *(this->selectedWord) ;
}

bool Worker::select( int index ) {
    bool flag = false ;
    if ( this->getCodeLength() > 0 ) {
        index = this->pageStartIndex + index ;
        const lookup::Candidate* candidate = this->lookup->getCandidate( index ) ;

        if ( candidate ) {
            qreal freq = -0x1000 ;
            if ( this->selectedWord->isEmpty() ) {
                int halfIndex = ( candidate->second + index ) / 2 ;
                if ( halfIndex < 2 ) 
                    halfIndex = 0 ;
                const lookup::Candidate* candidate = this->lookup->getCandidate( halfIndex ) ;
                freq = lookup::get_freq( candidate ) ;
                if ( freq <= 0.1 ) 
                    freq = 1.1 ;
                else 
                    freq += 1 ;
            }
            
            const QString* key = lookup::get_key( candidate ) ;
            const QString* preedit = lookup::get_preedit( candidate ) ;
            const QString* word = lookup::get_word( candidate ) ;
            append_selected( this->selected, key, preedit, word, -0x1000 ) ;
            this->selected->second.second.last() = freq ;

            this->candidate = candidate ;
            if ( this->getInvalidCodeLength() > 0 ) {
                QString code( this->getInvalidCode() ) ;
                this->lookup->clearCode() ;
                this->lookup->setCode( code ) ;
            }
            else 
                this->lookup->clearCode() ;
            this->pageStartIndex = 0 ;

            flag = true ;
        }
    }
    return flag ;
}

bool Worker::deselect() {
    bool flag = false ;
    if ( !this->selectedWord->isEmpty() ) {
        QString code ;
        pop_selected( this->selected, &code ) ;

        if ( this->lookup == this->t9Lookup ) {
            for ( int i = 0, l = code.length() ; i < l ; i++ ) 
                code[i] = this->t9Lookup->tree.trans[ code.at(i).toAscii() - 'a' ] ;
        }

        code.append( this->lookup->code ) ;
        this->lookup->clearCode() ;
        this->lookup->setCode( code ) ;
        this->pageStartIndex = 0 ;

        flag = true ;
    }
    return flag ;
}
void Worker::reset() {
    this->lookup->clearCode() ;
    clear_selected( this->selected ) ;
    this->pageStartIndex = 0 ;
}

bool Worker::appendCode( QChar code ) {
    //bool flag = false ;
    this->lookup->appendCode( code ) ;
    this->pageStartIndex = 0 ;
    return true ;
}

bool Worker::popCode() {
    bool flag = false ;
    if ( !this->lookup->code.isEmpty() ) {
        this->lookup->popCode() ;
        this->pageStartIndex = 0 ;
        flag = true ;
    }
    return flag ;
}

void Worker::commit() {
    if ( this->selectedWord->length() < 6 ) {
        const QString* key = &(this->selected->first.first) ;
        qreal freq = this->selected->second.second.last() ;
        //freq = this->lookup->dict.update( *key, *(this->selectedWord), freq ) ;
        this->dict->insert( *key, *(this->selectedWord), freq ) ;
        if ( key->count( QChar('\'') ) <= 0 )
            split::add_key( &(this->pinyinLookup->keySet), *key ) ;
        fit::add_key( &(this->pinyinLookup->keyMap), *key ) ;
        this->t9Lookup->tree.addKey( *key ) ;
        //if ( this->logFile ) {
            //(*this->textStream) << *key << QChar( ' ' ) << *(this->selectedWord) << QChar( ' ' ) << freq << QChar( '\n' ) ;
            //this->flushLog() ;
        //}
    }
    this->reset() ;
}

bool Worker::setKeyboardLayout( Worker::KeyboardLayout layout ) {
    if ( layout != this->keyboardLayout ) {
        if ( layout == FullKeyboardLayout )
            this->lookup = this->pinyinLookup ;
        else if ( layout == T9KeyboardLayout )
            this->lookup = this->t9Lookup ;
        this->reset() ;
        this->keyboardLayout = layout ;
        return true ;
    }
    else
        return false ;
}

}

