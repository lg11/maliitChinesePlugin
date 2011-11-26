#ifndef KEYFILTER_H
#define KEYFILTER_H

//#include <QObject>

#include <QKeyEvent>
#include <QHash>

//#define IS_MODIFITY_KEY( keycode ) ( keycode == Qt::Key_Shift || keycode == QT::Key_Alt || keyCode == Qt::Key_Ctrl )

//#include <QDebug>

namespace inputmethod {

class KeyFilter {
public :
    enum KeyMask {
        MASK_SHIFT = 0x0001 ,
        MASK_CTRL = 0x0002 ,
        MASK_ALT = 0x0004 ,
        MASK_FN = 0x0008 ,
        MASK_META = 0x0010 
    } ;
    QHash<int, bool> record ;
    QHash<int, int> hash ;
    int mask:5 ;
    int clearFlag:5 ;
    int dirtyFlag:5 ;
    int stickyKey:5 ;
    int stickyMask:5 ;
    int fixed:7 ; 

    KeyFilter() ;
    ~KeyFilter() ;
    bool setMask( KeyMask MASK ) ;
    bool unsetMask( KeyMask MASK ) ;
    bool filter( QEvent::Type type, int keycode, Qt::KeyboardModifiers modifiers, const QString& text, bool autoRepeat, int count ) ;
    int remap( int src ) ;
    void setRemap( int src, int dest ) ;
    void unsetRemap( int src ) ;
} ;

KeyFilter::KeyFilter() :
    record() ,
    hash() ,
    mask( 0 ) ,
    clearFlag( 0 ) ,
    dirtyFlag( 0 ) ,
    stickyKey( 0 ) ,
    stickyMask( 0 )
{
    this->stickyKey |= MASK_SHIFT ;
    this->stickyKey |= MASK_FN ;
}

KeyFilter::~KeyFilter() {
}

bool KeyFilter::setMask( KeyMask MASK ) {
    this->mask |= MASK ;
    this->clearFlag |= MASK ;
    this->dirtyFlag &= ~MASK ;
    this->stickyMask |= MASK & this->stickyKey ;
    return true ;
}

bool KeyFilter::unsetMask( KeyMask MASK ) {
    this->clearFlag |= MASK ;
    this->mask &= ~MASK ;
    if ( this->dirtyFlag & MASK ) {
        this->stickyMask &= ~MASK ;
        return true ;
    }
    else
        return false ;
}

bool KeyFilter::filter( QEvent::Type type, int keycode, Qt::KeyboardModifiers modifiers, const QString& text, bool autoRepeat, int count ) {
    Q_UNUSED( modifiers ) ;
    Q_UNUSED( text ) ;
    Q_UNUSED( count ) ;

    bool flag = false ;
    this->clearFlag &= 0 ;
    if ( autoRepeat )
        flag = true ;
    else {
        switch ( keycode ) {
            case Qt::Key_Shift :
                if ( type == QEvent::KeyPress ) 
                    flag = this->setMask( MASK_SHIFT ) ;
                else if ( type == QEvent::KeyRelease ) 
                    flag = this->unsetMask( MASK_SHIFT ) ;
                break ;
            case Qt::Key_Control :
                if ( type == QEvent::KeyPress ) 
                    flag = this->setMask( MASK_CTRL ) ;
                else if ( type == QEvent::KeyRelease ) 
                    flag = this->unsetMask( MASK_CTRL ) ;
                break ;
            case Qt::Key_Alt :
                if ( type == QEvent::KeyPress ) 
                    flag = this->setMask( MASK_ALT ) ;
                else if ( type == QEvent::KeyRelease ) 
                    flag = this->unsetMask( MASK_ALT ) ;
                break ;
            case Qt::Key_AltGr :
                if ( type == QEvent::KeyPress ) 
                    flag = this->setMask( MASK_FN ) ;
                else if ( type == QEvent::KeyRelease ) 
                    flag = this->unsetMask( MASK_FN ) ;
                break ;
            default :
                if ( type == QEvent::KeyPress ) {
                    this->record.insert( keycode, true ) ;
                }
                else if ( type == QEvent::KeyRelease ) {
                    if ( this->record.contains( keycode ) && this->record.value( keycode ) ) {
                        this->record.insert( keycode, false ) ;
                        flag = true ;
                    }
                }
        }
    }

    this->stickyMask &= this->clearFlag | this->mask ;
    this->clearFlag ^= -1 ;
    this->dirtyFlag |= this->clearFlag ;

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
