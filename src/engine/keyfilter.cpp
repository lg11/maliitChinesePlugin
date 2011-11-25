#include "keyfilter.h"

#include <QHash>

//#include <QDebug>

namespace engine {

class KeyFilterPrivate {
public :
    QHash< Qt::Key, bool > record ;
    KeyFilterPrivate() : record() {} 
    ~KeyFilterPrivate() {}
} ;

KeyFilter::KeyFilter() :
    d_ptr( new KeyFilterPrivate )
{
}

KeyFilter::~KeyFilter() {
    delete this->d_ptr ;
}

bool KeyFilter::filter( QEvent::Type keyType, Qt::Key keyCode, Qt::KeyboardModifiers modifiers, const QString& text, bool autoRepeat, int count ) {
    Q_D( KeyFilter ) ;
    bool flag = false ;
    if ( autoRepeat )
        flag = true ;
    else if ( keyType == QEvent::KeyPress ) {
        d->record.insert( keyCode, true ) ;
    }
    else if ( keyType == QEvent::KeyRelease ) {
        if ( d->record.contains( keyCode ) && d->record.value( keyCode ) ) {
            flag = true ;
            d->record.insert( keyCode, false ) ;
        }
    }
    return flag ;
}

}

