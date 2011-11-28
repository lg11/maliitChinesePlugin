#ifndef SPLIT_H
#define SPLIT_H

#include <QString>
#include <QList>
#include <QStringList>
#include <QPair>
#include <QSet>

//#include <QDebug>

namespace split {

typedef QPair< QSet<QString>, QPair< QSet<QChar>, QSet<QString> > > KeySet ;
// KeySet.first : full key string, ie (pinyin) : long -> long
// KeySet.second.first : first char of key, ie (pinyin) : l -> long
// KeySet.second.first : incompleted key, ie (pinyin) : lon -> long

inline void add_key( KeySet* set, const QString& key ) {
    if ( !set->first.contains( key ) ) {
        set->first.insert( key ) ;
        set->second.first.insert( key.at(0) ) ;
        set->second.second.remove( key ) ;
        QString k( key ) ;
        k.chop( 1 ) ;
        while( k.length() > 0 ) {
            if ( !set->first.contains( k ) )
                set->second.second.insert( k ) ;
            k.chop( 1 ) ;
        }
    }
}

inline bool check_complete( const KeySet* set, const QString& key ) { return set->first.contains( key ) ; } 
inline bool check_head( const KeySet* set, QChar head ) { return set->second.first.contains( head ) ; } 
inline bool check_valid( const KeySet* set, const QString& key ) { return set->first.contains( key ) ? true : set->second.second.contains( key ) ; } 

typedef QPair< QStringList, QPair<int,int> > KeyString ;
// KeyString.first : stringList of key, ie (pinyin) : san'ge'ri
// KeyString.second.first : string length, ie (pinyin) : 7 -> san'ge'ri
// KeyString.second.second : string splited start length
typedef QList<KeyString> KeyList ;

inline void append_code( KeyList* list, QChar code, const KeySet* set, KeyString* string ) {
    QString* tail = &(string->first.last()) ;
    bool flag = check_complete( set, *tail ) && check_head( set, code ) ;
    tail->append( code ) ;
    if ( check_valid( set, *tail ) ) {
        if ( flag ) {
            list->append( *string ) ;
            KeyString* new_string = &(list->last()) ;
            new_string->first.last().chop( 1 ) ;
            new_string->first.append( code ) ;
            new_string->second.first++ ;
            new_string->second.second = string->second.first ;
        }
        string->second.first++ ;
    }
    else {
        tail->chop( 1 ) ;
        if ( check_head( set, code ) ) {
            string->first.append( code ) ;
            string->second.first++ ;
        }
    }
}

inline void pop_code( KeyString* string ) {
    if ( string->second.first > 0 ) {
        if ( string->first.last().length() > 1 )
            string->first.last().chop( 1 ) ;
        else 
            string->first.removeLast() ;
        string->second.first-- ;
    }
}

inline void append_code( KeyList* list, QChar code, const KeySet* set, int code_length ) {
    QList<KeyString*> buffer ;
    for ( int i = 0, l = list->length() ; i < l ; i++ )
        buffer.append( &((*list)[i]) ) ;
    for ( int i = 0, l = buffer.length() ; i < l ; i++ ) {
        KeyString* string = buffer[i] ;
        if ( string->second.first >= code_length ) 
            append_code( list, code, set, string ) ;
    }
}

inline void pop_code( KeyList* list, int code_length ) {
    QList<int> buffer ;
    for ( int i = 0, l = list->length() ; i < l ; i++ ) {
        KeyString* string = &((*list)[i]) ;
        if ( string->second.first > code_length ) {
            pop_code( string ) ;
            if ( string->second.first <= string->second.second )
                buffer.append( i ) ;
        }
    }
    int count = 0 ;
    for ( int i = 0, l = buffer.length() ; i < l ; i++ ) {
        int index = buffer.at(i) ;
        list->removeAt( index - count ) ;
        count++ ;
    }
    if ( list->isEmpty() ) 
        list->append( KeyString( QStringList( QString() ), QPair<int, int>() ) ) ;
}

inline void clear_code( KeyList* list ) {
    list->clear() ;
    list->append( KeyString( QStringList( QString() ), QPair<int, int>() ) ) ;
}

}

#endif
