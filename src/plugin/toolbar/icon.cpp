#include "icon.h"

#include <QPixmap>

#include <MTheme>

namespace toolbar {

class IconPrivate {
public :
    const QPixmap* pixmap ;
    QString iconId ;
    QString iconPath ;
    qreal paintedWidth ;
    qreal paintedHeight ;
    IconPrivate() :
        pixmap( 0 ) ,
        iconId() ,
        iconPath() ,
        paintedWidth( 0 ) ,
        paintedHeight( 0 ) 
    {
    }
    void releasePixmap() {
        if ( this->pixmap ) {
            if ( !this->iconId.isEmpty() ) {
                this->iconId.clear() ;
                MTheme::releasePixmap( this->pixmap ) ;
            }
            else if ( !this->iconPath.isEmpty() ) {
                this->iconPath.clear() ;
                delete this->pixmap ;
            }
            this->pixmap = 0 ;
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

void Icon::checkPaintedSize() {
    Q_D( Icon ) ;
    qreal paintedWidth = 0 ;
    qreal paintedHeight = 0 ;
    if ( d->pixmap ) {
        paintedWidth = d->pixmap->width() ;
        paintedHeight = d->pixmap->height() ;
    }
    if ( d->paintedWidth != paintedWidth ) {
        d->paintedWidth = paintedWidth ;
        emit this->paintedWidthChanged( d->paintedWidth ) ;
    }
    if ( d->paintedHeight != paintedHeight ) {
        d->paintedHeight = paintedHeight ;
        emit this->paintedHeightChanged( d->paintedHeight ) ;
    }
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
        if ( !d->iconId.isEmpty() ) {
            d->pixmap = MTheme::pixmap( iconId, QSize( 32, 32 ) ) ;
        }
        this->checkPaintedSize() ;
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
        if ( !d->iconPath.isEmpty() ) {
            d->pixmap = new QPixmap( iconPath ) ;
        }
        this->checkPaintedSize() ;
    }
}

qreal Icon::getPaintedWidth() const {
    Q_D( const Icon ) ;
    return d->paintedWidth ;
}

qreal Icon::getPaintedHeight() const {
    Q_D( const Icon ) ;
    return d->paintedHeight ;
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

