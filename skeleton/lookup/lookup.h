#ifndef LOOKUP_H
#define LOOKUP_H

#include <QHash>
#include <QList>
#include <QString>
#include <QPair>
#include <QSet>

#include "split.h"
#include "fit.h"
#include "pick.h"
#include "dict.h"

//#include <QDebug>

namespace lookup {

typedef QPair<const QString*, const QString*> KeyPair ;
typedef QPair<const QString*, qreal > WordPair ;
typedef QPair<KeyPair, WordPair> CandPair ;
typedef QPair<CandPair, int> Candidate ;

inline const QString* get_key( Candidate* cand ) { return cand->first.first.first ; }
inline const QString* get_preedit( Candidate* cand ) { return cand->first.first.second ; }
inline const QString* get_word( Candidate* cand ) { return cand->first.second.first ; }
inline qreal get_freq( Candidate* cand ) { return cand->first.second.second ; }

typedef QPair< int, QPair< QList<const QString*>, QList<const QString*> > > LookupPair ;

class Lookup {
public :
    dict::Dictionary dict ;
    split::Spliter spliter ;
    fit::KeyMap keyMap ;
    QList<pick::PickPair> pickCache ;
    QList<LookupPair> lookupCache ;
    QList< QList<QString> > preeditCache ;
    QSet<QString> usedKeySet ;
    int candCacheIndex ;
    int candStartIndex ;
    QList<Candidate> candList ;

    inline Lookup() : dict(), spliter(), keyMap(), pickCache(), lookupCache(), preeditCache(), usedKeySet(), candCacheIndex(0), candStartIndex(0), candList() {}

    inline void appendCode( QChar code ) {
        this->pickCache.clear() ;
        this->usedKeySet.clear() ;
        this->spliter.appendCode( code ) ;
        this->lookupCache.append( LookupPair() ) ;
        this->preeditCache.append( QList<QString>() ) ;

        QList<const QString*>* key = &(this->lookupCache.last().second.first)  ;
        QList<const QString*>* preedit = &(this->lookupCache.last().second.second)  ;
        QList<QString>* preeditCache = &(this->preeditCache.last())  ;
        
        int highestPoint = -0x1000 ;
        for ( int i = 0 ; i < spliter.stringList.length() ; i++ ) {
            int fitPoint ;
            QList<const QString*> buffer ;
            fit::fit( &(this->spliter.stringList[i].first), &buffer, &fitPoint, &(this->keyMap) ) ;
            if ( fitPoint > highestPoint ) {
                highestPoint = fitPoint ;
                preeditCache->clear() ;
                key->clear() ;
                preedit->clear() ;
                preeditCache->append( this->spliter.stringList[i].first.join( "'" ) ) ;
                foreach( const QString* s, buffer ) {
                    key->append( s ) ;
                    preedit->append( &(preeditCache->last()) ) ;
                }
            }
            else if ( fitPoint == highestPoint ) {
                preeditCache->append( this->spliter.stringList[i].first.join( "'" ) ) ;
                foreach( const QString* s, buffer ) {
                    key->append( s ) ;
                    preedit->append( &(preeditCache->last()) ) ;
                }
            }
        }
        this->lookupCache.last().first = highestPoint ;
        pick::set( &(this->pickCache), key, preedit, &(this->dict.hash) ) ;
        foreach( const QString* k, *key )
            this->usedKeySet.insert( *k ) ;
        this->candList.clear() ;
        this->candCacheIndex = this->lookupCache.length() - 1 ;
        this->candStartIndex = 0 ;
    }
    inline void popCode() {
        this->pickCache.clear() ;
        this->usedKeySet.clear() ;
        this->spliter.popCode() ;
        this->lookupCache.removeLast() ;
        this->preeditCache.removeLast() ;

        if ( !this->lookupCache.isEmpty() ) {
            QList<const QString*>* key = &(this->lookupCache.last().second.first)  ;
            QList<const QString*>* preedit = &(this->lookupCache.last().second.second)  ;
            pick::set( &(this->pickCache), key, preedit, &(this->dict.hash), &(this->usedKeySet) ) ;
            foreach( const QString* k, *key )
                this->usedKeySet.insert( *k ) ;
            this->candList.clear() ;
            this->candCacheIndex = this->lookupCache.length() - 1 ;
            this->candStartIndex = 0 ;
        }
    }
    inline void reset() {
        this->pickCache.clear() ;
        this->usedKeySet.clear() ;
        this->spliter.clear() ;
        this->lookupCache.clear() ;
        this->preeditCache.clear() ;
        this->candCacheIndex = 0 ;
        this->candStartIndex = 0 ;
    }
    inline void setCode( const QString& code ) {
        this->reset() ;
        for( int i = 0 ; i < code.length() ; i++ )
            this->appendCode( code.at(i) ) ;
    }
    inline bool checkCache() {
        bool flag = false ;
        if ( this->candCacheIndex >= 0 ) {
            this->pickCache.clear() ;
            QList<const QString*>* key ;
            QList<const QString*>* preedit ;
            int prevPoint = this->lookupCache[this->candCacheIndex].first ;
            int fitPoint ;

            this->candCacheIndex-- ;
            while ( !flag && this->candCacheIndex >= 0 ) {
                fitPoint = this->lookupCache[this->candCacheIndex].first ;
                if ( fitPoint >= prevPoint ) {
                    key = &(this->lookupCache[this->candCacheIndex].second.first)  ;
                    preedit = &(this->lookupCache[this->candCacheIndex].second.second)  ;
                    if ( !key->isEmpty() ) {
                        //qDebug() << fitPoint << prevPoint << *(preedit->at(0)) ;
                        flag = true ;
                    }
                }
                if ( !flag )
                    this->candCacheIndex-- ;
            }
            if ( flag ) {
                this->lookupCache[this->candCacheIndex].first = fitPoint ;
                pick::set( &(this->pickCache), key, preedit, &(this->dict.hash) ) ;
            }
        }
        return flag ;
    }
    inline const Candidate* getCand( int index ) {
        bool flag = true ;
        while ( flag && this->candList.length() <= index ) {
            const QString* key ; const QString* preedit ; const QString* word ; qreal freq ;
            pick::pick( &(this->pickCache), &key, &preedit, &word, &freq ) ;
            if ( key ) 
                this->candList.append( Candidate( CandPair( KeyPair( key, preedit ), WordPair( word, freq ) ), this->candStartIndex ) ) ;
            else {
                flag = this->checkCache() ;
                this->candStartIndex = this->candList.length() ;
            }
        }
        if ( flag ) 
            return &(this->candList.at(index)) ; 
        else 
            return NULL ;
    }
};

}

#endif