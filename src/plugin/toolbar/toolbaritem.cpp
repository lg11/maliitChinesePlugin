#include "toolbaritem.h"

#include <mtoolbaritem.h>

namespace toolbar {

class ToolbarItemPrivate {
public :
    MToolbarItem* item ;
    QString text ;
    QString iconId ;
    QString iconPath ;
    int size ;
    Qt::Alignment alignment ;
    ToolbarItemPrivate() : \
        item( 0 ), \
        text(), \
        iconId(), \
        iconPath(), \
        size( 0 ),
        alignment( Qt::AlignCenter )
    {
    }
    ~ToolbarItemPrivate() {}
} ;

ToolbarItem::ToolbarItem( QObject* parent ) : QObject( parent ), d_ptr( new ToolbarItemPrivate() ) {
}

ToolbarItem::~ToolbarItem() {
    delete this->d_ptr ;
}

const QString& ToolbarItem::getText() const {
    Q_D( const ToolbarItem ) ;
    return d->text ;
}

void ToolbarItem::setText( const QString& text ) {
    Q_D( ToolbarItem ) ;
    if ( d->text != text ) {
        d->text = text ;
        emit this->textChanged( d->text ) ;
    }
}

const QString& ToolbarItem::getIconId() const {
    Q_D( const ToolbarItem ) ;
    return d->iconId ;
}

void ToolbarItem::setIconId( const QString& iconId ) {
    Q_D( ToolbarItem ) ;
    if ( d->iconId != iconId ) {
        if ( !d->iconPath.isEmpty() ) {
            d->iconPath.clear() ;
            emit this->iconPathChanged( QString("") ) ;
        }
        d->iconId = iconId ;
        emit this->iconIdChanged( d->iconId ) ;
    }
}

const QString& ToolbarItem::getIconPath() const {
    Q_D( const ToolbarItem ) ;
    return d->iconPath ;
}

void ToolbarItem::setIconPath( const QString& iconPath ) {
    Q_D( ToolbarItem ) ;
    if ( d->iconPath != iconPath ) {
        if ( !d->iconId.isEmpty() ) {
            d->iconId.clear() ;
            emit this->iconIdChanged( QString("") ) ;
        }
        d->iconPath = iconPath ;
        emit this->iconPathChanged( d->iconPath ) ;
    }
}

int ToolbarItem::getSize() const {
    Q_D( const ToolbarItem ) ;
    return d->size ;
}

void ToolbarItem::setSize( int size ) {
    Q_D( ToolbarItem ) ;
    if ( d->size != size ) {
        d->size = size ;
        emit this->sizeChanged( d->size ) ;
    }
}

Qt::Alignment ToolbarItem::getAlignment() const {
    Q_D( const ToolbarItem ) ;
    return d->alignment ;
}

void ToolbarItem::setAlignment( Qt::Alignment alignment ) {
    Q_D( ToolbarItem ) ;
    alignment = alignment & ( Qt::AlignLeft | Qt::AlignRight ) ;
    if ( d->alignment != alignment ) {
        d->alignment = alignment ;
        emit this->alignmentChanged( d->alignment ) ;
    }
}

} 
