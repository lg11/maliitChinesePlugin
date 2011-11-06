#include "icon.h"

#include <QPixmap>

#include <MTheme>

namespace toolbar {

class IconPrivate {
public :
    const QPixmap* pixmap ;
    QString iconId ;
    QString iconPath ;
    IconPrivate() : \
        pixmap( 0 ), \
        iconId(), \
        iconPath()
    {
    }
    void releasePixmap() {
        if ( !this->iconId.isEmpty() ) {
            this->iconId.clear() ;
            MTheme::releasePixmap( this->pixmap ) ;
        }
        else if ( !this->iconPath.isEmpty() ) {
            this->iconPath.clear() ;
            delete this->pixmap ;
        }
    }
    ~IconPrivate() {
        this->releasePixmap() ;
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

const QString& Icon::getIconId() const {
    Q_D( const Icon ) ;
    return d->iconId ;
}

void Icon::setIconId( const QString& iconId ) {
    Q_D( Icon ) ;
    if ( d->iconId != iconId ) {
        d->releasePixmap() ;
        d->iconId = iconId ;
        d->pixmap = MTheme::pixmap( iconId, QSize( 32, 32 ) ) ;
    }
}

const QString& Icon::getIconPath() const {
    Q_D( const Icon ) ;
    return d->iconPath ;
}

void Icon::setIconPath( const QString& iconPath ) {
    Q_D( Icon ) ;
    if ( d->iconPath != iconPath ) {
        d->releasePixmap() ;
        d->iconPath = iconPath ;
        d->pixmap = new QPixmap( iconPath ) ;
    }
}

void Icon::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ) {
    Q_D( const Icon ) ;
    Q_UNUSED( option )
    Q_UNUSED( widget )
    //qDebug() << "icon_paint" ;
    if ( d->pixmap ) 
        painter->drawPixmap( this->boundingRect(), *(d->pixmap), QRectF(d->pixmap->rect()) ) ;
        //painter->drawPixmap( this->boundingRect(), *(d->pixmap), QRectF(d->pixmap->rect()) ) ;
}

}

