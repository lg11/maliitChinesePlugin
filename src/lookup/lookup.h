#ifndef LOOKUP_H
#define LOOKUP_H

#include "dict.h"

#include <QPair>
#include <QString>

namespace lookup {

typedef QPair<const QString*, const QString*> KeyPair ;
typedef QPair<const QString*, qreal > WordPair ;
typedef QPair<KeyPair, WordPair> CandPair ;
typedef QPair<CandPair, int> Candidate ;

inline const QString* get_key( const Candidate* cand ) { return cand->first.first.first ; }
inline const QString* get_preedit( const Candidate* cand ) { return cand->first.first.second ; }
inline const QString* get_word( const Candidate* cand ) { return cand->first.second.first ; }
inline qreal get_freq( const Candidate* cand ) { return cand->first.second.second ; }

inline void check_cand( QList<Candidate>* cand_list, int length ) {
    if ( length >= cand_list->length() ) 
        cand_list->append( Candidate( CandPair( KeyPair( NULL, NULL ), WordPair( NULL, 0 ) ), 0 ) ) ;
}

inline void set_cand( Candidate* cand, const QString* key, const QString* preedit, const QString* word, qreal freq, int start_index ) {
    cand->first.first.first = key ;
    cand->first.first.second = preedit ;
    cand->first.second.first = word ;
    cand->first.second.second = freq ;
    cand->second = start_index ;
}

typedef QPair< int, QPair< QList<const QString*>, QList<const QString*> > > LookupPair ;

class Lookup {
public :
    QString code ;
    dict::Dictionary* dict ;
    Lookup( dict::Dictionary* dict ) : code(), dict( dict ) {}
    virtual void appendCode( QChar code ) = 0 ;
    virtual void popCode() = 0 ;
    virtual void clearCode() = 0 ;
    virtual void setCode( const QString& code ) = 0 ;
    virtual const Candidate* getCandidate( int index ) = 0 ;
} ;

}

#endif
