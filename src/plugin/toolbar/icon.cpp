#include "icon.h"

#include <QPixmap>

#include <MTheme>
#include <mbuttonstyle.h>

namespace toolbar {

class IconPrivate {
public :
    const QPixmap* pixmap ;
    QString iconId ;
    QString iconPath ;
    const MStyle* style ;
    IconPrivate() : \
        pixmap( 0 ), \
        iconId(), \
        iconPath()
    {
        this->style = MTheme::style( "MButtonStyle", QString(""), QString("active"), QString("default"), M::Landscape ) ;
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
        MTheme::releaseStyle( this->style ) ;
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
        const MButtonStyle* style = static_cast<const MButtonStyle*>(d->style) ;
        d->pixmap = MTheme::pixmap( iconId, style->iconSize() ) ;
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

