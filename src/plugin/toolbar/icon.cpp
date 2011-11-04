#include "icon.h"

#include <QPixmap>

#include <MTheme>
#include <mbuttonstyle.h>

namespace toolbar {

class IconPrivate {
public :
    const QPixmap* pixmap ;
    QString iconId ;
    const MStyle* style ;
    IconPrivate() : \
        pixmap( 0 ), \
        iconId()
    {
        this->style = MTheme::style( "MButtonStyle", QString(""), QString("active"), QString("default"), M::Landscape ) ;
    }
    ~IconPrivate() {
        if ( !this->iconId.isEmpty() )
            MTheme::releasePixmap( this->pixmap ) ;
        MTheme::releaseStyle( this->style ) ;
        //else if ( this->pixmap )
            //delete this->pixmap ;
    }
} ;

Icon::Icon( QDeclarativeItem* parent ) : \
        QDeclarativeItem( parent ), \
        d_ptr( new IconPrivate )
{
    this->setFlag( QGraphicsItem::ItemHasNoContents, false) ;
}

Icon::~Icon() {
    delete this->d_ptr ;
}

const QString& Icon::getIconId() {
    Q_D( const Icon ) ;
    return d->iconId ;
}

void Icon::setIconId( const QString& iconId ) {
    Q_D( Icon ) ;
    if ( d->iconId != iconId ) {
        d->iconId = iconId ;
        if ( d->pixmap )
            MTheme::releasePixmap( d->pixmap ) ;
        const MButtonStyle* style = static_cast<const MButtonStyle*>(d->style) ;
        d->pixmap = MTheme::pixmap( iconId, style->iconSize() ) ;
    }
}

void Icon::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ) {
    Q_D( const Icon ) ;
    Q_UNUSED( option )
    Q_UNUSED( widget )
    qDebug() << "icon_paint" ;
    if ( d->pixmap ) 
        painter->drawPixmap( this->boundingRect(), *(d->pixmap), QRectF(d->pixmap->rect()) ) ;
        //painter->drawPixmap( this->boundingRect(), *(d->pixmap), QRectF(d->pixmap->rect()) ) ;
}

}

