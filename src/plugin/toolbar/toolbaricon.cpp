#include "toolbaricon.h"

#include <QPixmap>

//#include <MTheme>

namespace toolbar {

class ToolbarIconPrivate {
public :
    const QPixmap* pixmap ;
    QString iconId ;
    QString iconPath ;
    qreal paintedWidth ;
    qreal paintedHeight ;
    ToolbarIconPrivate() :
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
                //MTheme::releasePixmap( this->pixmap ) ;
            }
            else if ( !this->iconPath.isEmpty() ) {
                this->iconPath.clear() ;
                delete this->pixmap ;
            }
            this->pixmap = 0 ;
        }
    }
    ~ToolbarIconPrivate() {
        this->releasePixmap() ;
    }
} ;

ToolbarIcon::ToolbarIcon( QDeclarativeItem* parent ) : \
        QDeclarativeItem( parent ), \
        d_ptr( new ToolbarIconPrivate )
{
    this->setFlag( QGraphicsItem::ItemHasNoContents, false) ;
}

ToolbarIcon::~ToolbarIcon() {
    delete this->d_ptr ;
}

void ToolbarIcon::checkPaintedSize() {
    Q_D( ToolbarIcon ) ;
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

const QString& ToolbarIcon::getIconId() const {
    Q_D( const ToolbarIcon ) ;
    return d->iconId ;
}

void ToolbarIcon::setIconId( const QString& iconId ) {
    Q_D( ToolbarIcon ) ;
    if ( d->iconId != iconId ) {
        d->releasePixmap() ;
        d->iconId = iconId ;
        if ( !d->iconId.isEmpty() ) {
            //d->pixmap = MTheme::pixmap( iconId, QSize( 32, 32 ) ) ;
        }
        this->checkPaintedSize() ;
    }
}

const QString& ToolbarIcon::getIconPath() const {
    Q_D( const ToolbarIcon ) ;
    return d->iconPath ;
}

void ToolbarIcon::setIconPath( const QString& iconPath ) {
    Q_D( ToolbarIcon ) ;
    if ( d->iconPath != iconPath ) {
        d->releasePixmap() ;
        d->iconPath = iconPath ;
        if ( !d->iconPath.isEmpty() ) {
            d->pixmap = new QPixmap( iconPath ) ;
        }
        this->checkPaintedSize() ;
    }
}

qreal ToolbarIcon::getPaintedWidth() const {
    Q_D( const ToolbarIcon ) ;
    return d->paintedWidth ;
}

qreal ToolbarIcon::getPaintedHeight() const {
    Q_D( const ToolbarIcon ) ;
    return d->paintedHeight ;
}


void ToolbarIcon::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ) {
    Q_D( const ToolbarIcon ) ;
    Q_UNUSED( option )
    Q_UNUSED( widget )
    //qDebug() << "icon_paint" ;
    if ( d->pixmap ) 
        painter->drawPixmap( this->boundingRect(), *(d->pixmap), QRectF(d->pixmap->rect()) ) ;
        //painter->drawPixmap( this->boundingRect(), *(d->pixmap), QRectF(d->pixmap->rect()) ) ;
}

}

