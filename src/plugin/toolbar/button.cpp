#include "button.h"

#include <QIcon>
#include <MButtonView>
#include <mtoolbaritem.h>

#include <QDebug>

namespace toolbar {

class ButtonPrivate {
public :
    QSharedPointer<MToolbarItem> item ;
    QIcon* icon ;
    QString iconFilePath ;
    ButtonPrivate( QSharedPointer<MToolbarItem> item ) : item( item ), icon( 0 ), iconFilePath() {}
} ;

Button::Button( QGraphicsItem *parent, QSharedPointer<MToolbarItem> item ) : MButton( parent ), d_ptr( new ButtonPrivate( item ) ) {
    this->setViewType( MButton::defaultType ) ;

    Q_D( Button ) ;

    if ( !d->item->name().isEmpty() ) 
        this->setObjectName( d->item->name() ) ;
    if ( !d->item->iconId().isEmpty() )
        this->setIconID( d->item->iconId() ) ;
    else 
        this->setIconFile( d->item->icon() ) ;

    //if ( !item->textId().isEmpty() )
        //setText( qtTrId(this->item->textId().toUtf8().data()) ) ;
    //if (!this->item->text().isEmpty()) {
        //setText(this->item->text());
    //}
    this->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum ) ;
    //qDebug() << "size" ;
    //qDebug() << this->preferredSize().width() ;
    //qDebug() << this->preferredSize().height() ;
}

Button::~Button() {
}

void Button::setIconFile( const QString& path ) {
    Q_D( Button ) ;
    if ( path != d->iconFilePath ) {
        if ( d->icon )
            delete d->icon ;
        d->icon = new QIcon( path ) ;
        this->setIcon( *(d->icon) ) ;
    }
}

}

