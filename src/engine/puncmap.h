#ifndef PUNCMAP_H
#define PUNCMAP_H

#include <QHash>
#include <QString>

//#include <QDebug>

namespace engine {
 
class PuncMap {
public :
    QHash<QChar, QString> hash ;
    bool quoteFlag[2] ;
    QString quoteString[2][2] ;
    //const QString* result ;

    PuncMap() ;
    ~PuncMap() ;
    const QString* remap( QChar src ) ;
    void setRemap( QChar src, const QString& dest ) ;
    void unsetRemap( QChar src ) ;
} ;

PuncMap::PuncMap() :
    hash() 
    //result( 0 )
{
    this->quoteFlag[0] = false ;
    this->quoteFlag[1] = false ;
    this->quoteString[0][0] = QString( QChar(0x2018) ) ;
    this->quoteString[0][1] = QString( QChar(0x2019) ) ;
    this->quoteString[1][0] = QString( QChar(0x201c) ) ;
    this->quoteString[1][1] = QString( QChar(0x201d) ) ;
}

PuncMap::~PuncMap()
{
}

const QString* PuncMap::remap( QChar src ) {
    const QString* dest ;
    if ( this->hash.contains( src ) ) {
        dest = &(this->hash[src]) ;
        if ( dest->at(0) == this->quoteString[0][0].at(0) ) {
            if ( this->quoteFlag[0] )
                dest = &(this->quoteString[0][1]) ;
            this->quoteFlag[0] = !this->quoteFlag[0] ;
        }
        else if ( dest->at(0) == this->quoteString[1][0].at(0) ) {
            if ( this->quoteFlag[1] )
                dest = &(this->quoteString[1][1]) ;
            this->quoteFlag[1] = !this->quoteFlag[1] ;
        }
        return dest ;
    }
    else
        return 0 ;
}

void PuncMap::setRemap( QChar src, const QString& dest ) {
    this->hash.insert( src, dest ) ;
}

void PuncMap::unsetRemap( QChar src ) {
    this->hash.remove( src ) ;
}

}

#endif // PUNCMAP_H
