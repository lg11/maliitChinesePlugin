#include "item.h"

#include <mtoolbaritem.h>

namespace toolbar {

class ItemPrivate {
public :
    MToolbarItem* item ;
    QString text ;
    ItemPrivate() : \
        item( 0 ), \
        text() \
    {
    }
    ~ItemPrivate() {}
} ;

Item::Item( QObject* parent ) : QObject( parent ), d_ptr( new ItemPrivate() ) {
}

Item::~Item() {
    delete this->d_ptr ;
}

const QString& Item::getText() {
    Q_D( const Item ) ;
    return d->text ;
}

void Item::setText( const QString& text ) {
    Q_D( Item ) ;
    d->text = text ;
}

} 
