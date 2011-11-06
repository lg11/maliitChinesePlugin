#include "item.h"

#include <mtoolbaritem.h>

namespace toolbar {

class ItemPrivate {
public :
    MToolbarItem* item ;
    QString text ;
    QString iconId ;
    QString iconPath ;
    int size ;
    Qt::Alignment alignment ;
    ItemPrivate() : \
        item( 0 ), \
        text(), \
        iconId(), \
        iconPath(), \
        size( 0 ),
        alignment( Qt::AlignCenter )
    {
    }
    ~ItemPrivate() {}
} ;

Item::Item( QObject* parent ) : QObject( parent ), d_ptr( new ItemPrivate() ) {
}

Item::~Item() {
    delete this->d_ptr ;
}

const QString& Item::getText() const {
    Q_D( const Item ) ;
    return d->text ;
}

void Item::setText( const QString& text ) {
    Q_D( Item ) ;
    if ( d->text != text ) {
        d->text = text ;
        emit this->textChanged( d->text ) ;
    }
}

const QString& Item::getIconId() const {
    Q_D( const Item ) ;
    return d->iconId ;
}

void Item::setIconId( const QString& iconId ) {
    Q_D( Item ) ;
    if ( d->iconId != iconId ) {
        if ( !d->iconPath.isEmpty() ) {
            d->iconPath.clear() ;
            emit this->iconPathChanged( QString("") ) ;
        }
        d->iconId = iconId ;
        emit this->iconIdChanged( d->iconId ) ;
    }
}

const QString& Item::getIconPath() const {
    Q_D( const Item ) ;
    return d->iconPath ;
}

void Item::setIconPath( const QString& iconPath ) {
    Q_D( Item ) ;
    if ( d->iconPath != iconPath ) {
        if ( !d->iconId.isEmpty() ) {
            d->iconId.clear() ;
            emit this->iconIdChanged( QString("") ) ;
        }
        d->iconPath = iconPath ;
        emit this->iconPathChanged( d->iconPath ) ;
    }
}

int Item::getSize() const {
    Q_D( const Item ) ;
    return d->size ;
}

void Item::setSize( int size ) {
    Q_D( Item ) ;
    if ( d->size != size ) {
        d->size = size ;
        emit this->sizeChanged( d->size ) ;
    }
}

Qt::Alignment Item::getAlignment() const {
    Q_D( const Item ) ;
    return d->alignment ;
}

void Item::setAlignment( Qt::Alignment alignment ) {
    Q_D( Item ) ;
    alignment = alignment & ( Qt::AlignLeft | Qt::AlignRight ) ;
    if ( d->alignment != alignment ) {
        d->alignment = alignment ;
        emit this->alignmentChanged( d->alignment ) ;
    }
}

} 
