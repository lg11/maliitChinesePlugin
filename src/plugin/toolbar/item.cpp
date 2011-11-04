#include "item.h"

#include <mtoolbaritem.h>

namespace toolbar {

class ItemPrivate {
public :
    MToolbarItem* item ;
    QString text ;
    Qt::Alignment alignment ;
    ItemPrivate() : \
        item( 0 ), \
        text(), \
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

Qt::Alignment Item::getAlignment() const {
    Q_D( const Item ) ;
    return d->alignment ;
}

void Item::setAlignment( Qt::Alignment alignment ) {
    Q_D( Item ) ;
    if ( d->alignment != alignment ) {
        d->alignment = alignment ;
        emit this->alignmentChanged( d->alignment ) ;
    }
}

} 
