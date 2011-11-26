#ifndef KEYFILTER_H
#define KEYFILTER_H

//#include <QObject>

#include <QKeyEvent>
#include <QHash>

//#define IS_MODIFITY_KEY( keycode ) ( keycode == Qt::Key_Shift || keycode == QT::Key_Alt || keyCode == Qt::Key_Ctrl )

namespace inputmethod {

class KeyFilter {
public :
    QHash<int, bool> record ;
    QHash<int, int> hash ;
    int count ;
    //QHash<int, bool> modifi

    KeyFilter() ;
    ~KeyFilter() ;
    bool filter( QEvent::Type type, int keycode, Qt::KeyboardModifiers modifiers, const QString& text, bool autoRepeat, int count ) ;
    int remap( int src ) ;
    void setRemap( int src, int dest ) ;
    void unsetRemap( int src ) ;
} ;

KeyFilter::KeyFilter() :
    record() ,
    hash() ,
    count( 0 )
{
}

KeyFilter::~KeyFilter() {
}

bool KeyFilter::filter( QEvent::Type type, int keycode, Qt::KeyboardModifiers modifiers, const QString& text, bool autoRepeat, int count ) {
    Q_UNUSED( modifiers ) ;
    Q_UNUSED( text ) ;
    Q_UNUSED( count ) ;

    bool flag = false ;
    if ( autoRepeat )
        flag = true ;
    else if ( keycode == Qt::Key_Shift ) {
        if ( type == QEvent::KeyPress ) {
            flag = true ;
            this->count = 0 ;
        }
        else if ( this->count > 1 )
            flag = true ;
    }
    else if ( type == QEvent::KeyPress ) {
        this->record.insert( keycode, true ) ;
    }
    else if ( type == QEvent::KeyRelease ) {
        if ( this->record.contains( keycode ) && this->record.value( keycode ) ) {
            this->record.insert( keycode, false ) ;
            flag = true ;
        }
    }

    this->count++ ;

    return flag ;
}

int KeyFilter::remap( int src ) {
    if ( this->hash.contains( src ) )
        return this->hash.value( src ) ;
    else
        return src ;
}

void KeyFilter::setRemap( int src, int dest ) {
    this->hash.insert( src, dest ) ;
}

void KeyFilter::unsetRemap( int src ) {
    this->hash.remove( src ) ;
}

}

#endif // KEYFILTER_H
