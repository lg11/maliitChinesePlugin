#include "toolbardata.h"

#include <mtoolbarlayout.h>
#include <mtoolbaritem.h>

#include <QDebug>
#include <QIcon>
//#include <MTheme>

#include <QSharedPointer>

namespace toolbar {

class ToolbarDataPrivate {
public :
    QSharedPointer<const MToolbarData> ptr ;
    MInputMethod::Orientation orientation ;
    QList<ToolbarItem*>* items ;
    ToolbarDataPrivate() : ptr( 0 ), orientation( MInputMethod::Landscape ), items( new QList<ToolbarItem*>() ) {}
    ~ToolbarDataPrivate() {
        for ( int i = 0 ;  i < this->items->length() ; i++ )
            delete this->items->at(i) ;
        this->items->clear() ;
        delete this->items ;
    }
} ;

ToolbarData::ToolbarData( QObject* parent ) : \
    QObject( parent ), \
    d_ptr( new ToolbarDataPrivate() )
{
}

ToolbarData::~ToolbarData() {
    delete this->d_ptr ;
}

QDeclarativeListProperty<toolbar::ToolbarItem> ToolbarData::items() {
    Q_D( ToolbarData ) ;
    return QDeclarativeListProperty<toolbar::ToolbarItem>( this, *(d->items) ) ;
}

void ToolbarData::set( QSharedPointer<const MToolbarData> data ) {
    Q_D( ToolbarData ) ;
    if ( d->ptr != data ) {
        d->ptr = data ;
        this->updata() ;
    }
}

void ToolbarData::setOrientation( MInputMethod::Orientation orientation ) {
    Q_D( ToolbarData ) ;
    if ( d->orientation != orientation ) {
        d->orientation = orientation ;
        this->updata() ;
    }
}

void ToolbarData::setOrientation( int angle ) {
    switch( angle ) {
        case 0 :
            this->setOrientation( MInputMethod::Landscape ) ;
            break ;
        case 90 :
            this->setOrientation( MInputMethod::Portrait ) ;
            break ;
        case 180 :
            this->setOrientation( MInputMethod::Landscape ) ;
            break ;
        case 270 :
            this->setOrientation( MInputMethod::Portrait ) ;
            break ;
        default :
            break ;
    }
}

inline ToolbarItem* create_item( QSharedPointer<MToolbarItem> item ) {
    ToolbarItem* new_item = new ToolbarItem() ;

    if (item->alignment() == Qt::AlignLeft)
        new_item->setAlignment( Qt::AlignLeft | Qt::AlignVCenter ) ;
    else if (item->alignment() == Qt::AlignRight)
        new_item->setAlignment( Qt::AlignRight | Qt::AlignVCenter ) ;
    else
        new_item->setAlignment( Qt::AlignVCenter ) ;

    if ( !item->name().isEmpty() )
        new_item->setObjectName( item->name() );

    if ( !item->iconId().isEmpty() ) 
        new_item->setIconId( item->iconId() ) ;
    else 
        new_item->setIconPath( item->icon() ) ;

    if ( !item->textId().isEmpty() ) 
        new_item->setText( qtTrId(item->textId().toUtf8().data()) ) ;
    else if ( !item->text().isEmpty() ) 
        new_item->setText( item->text() ) ;

    new_item->setSize( item->size() ) ;

    /*
    updateItemVisibility(item);

    if (item->type() == MInputMethod::ItemButton) {
        widget = new MToolbarButton(item, sidebar);

        connect(widget, SIGNAL(clicked(MToolbarItem*)),
                this, SLOT(handleButtonClick(MToolbarItem*)));
    } else {
        widget = new MToolbarLabel(item, sidebar);
    }
    customWidgets.append(widget);
    // We should update the reaction map if the custom toolbar elements are changing.
    connect(widget, SIGNAL(geometryChanged()),
            &signalForwarder, SIGNAL(requestRepaint()), Qt::UniqueConnection);
    connect(widget, SIGNAL(displayEntered()),
            &signalForwarder, SIGNAL(requestRepaint()), Qt::UniqueConnection);
    connect(widget, SIGNAL(displayExited()),
            &signalForwarder, SIGNAL(requestRepaint()), Qt::UniqueConnection);
    if (sidebar->count() == 0) {
        // must be done before appending so that isVisible() tells the truth
        sidebar->show();
    }
    sidebar->append(widget, item->isVisible());
    */
    return new_item ;
}

void ToolbarData::updata() {
    Q_D( ToolbarData ) ;
    if ( d->ptr ) {
        QSharedPointer<const MToolbarLayout> layout = d->ptr->layout( d->orientation ) ;

        if ( !layout.isNull() ) {
            for ( int i = 0 ;  i < d->items->length() ; i++ )
                delete d->items->at(i) ;
            d->items->clear() ;
            foreach ( QSharedPointer<MToolbarItem> item, layout->items() ) {
                d->items->append( create_item( item ) ) ;
            }
            emit this->updated() ;
        }
    }
}

}
