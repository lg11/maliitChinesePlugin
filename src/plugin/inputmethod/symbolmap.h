#ifndef SYMBOLMAP_H
#define SYMBOLMAP_H

#include <QHash>
#include <QString>

//#include <QDebug>

namespace inputmethod {
 
class SymbolMap {
public :
    QHash<QChar, QString> hash ;
    //const QString* result ;

    SymbolMap() ;
    ~SymbolMap() ;
    const QString* remap( QChar src ) ;
    void setRemap( QChar src, const QString& dest ) ;
    void unsetRemap( QChar src ) ;
} ;

SymbolMap::SymbolMap() :
    hash() 
    //result( 0 )
{
}

SymbolMap::~SymbolMap()
{
}

const QString* SymbolMap::remap( QChar src ) {
    if ( this->hash.contains( src ) )
        return &(this->hash[src]) ;
    else
        return 0 ;
}

void SymbolMap::setRemap( QChar src, const QString& dest ) {
    this->hash.insert( src, dest ) ;
}

void SymbolMap::unsetRemap( QChar src ) {
    this->hash.remove( src ) ;
}

}

#endif // SYMBOLFILTER_H
