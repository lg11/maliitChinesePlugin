#include "data.h"

#include <mtoolbarlayout.h>
#include <mtoolbaritem.h>

#include <QDebug>
#include <QIcon>
#include <MTheme>

#include <QSharedPointer>

namespace toolbar {

class DataPrivate {
public :
    QSharedPointer<const MToolbarData> ptr ;
    MInputMethod::Orientation orientation ;
    QList<Item*>* items ;
    DataPrivate() : ptr( 0 ), orientation( MInputMethod::Landscape ), items( new QList<Item*>() ) {}
    ~DataPrivate() {
        for ( int i = 0 ;  i < this->items->length() ; i++ )
            delete this->items->at(i) ;
        this->items->clear() ;
        delete this->items ;
    }
} ;

Data::Data( QObject* parent ) : \
    QObject( parent ), \
    d_ptr( new DataPrivate() )
{
}

Data::~Data() {
    delete this->d_ptr ;
}

QDeclarativeListProperty<toolbar::Item> Data::items() {
    Q_D( Data ) ;
    return QDeclarativeListProperty<Item>( this, *(d->items) ) ;
}

void Data::set( QSharedPointer<const MToolbarData> data ) {
    Q_D( Data ) ;
    if ( d->ptr != data ) {
        d->ptr = data ;
        this->updata() ;
    }
}

void Data::setOrientation( MInputMethod::Orientation orientation ) {
    Q_D( Data ) ;
    if ( d->orientation != orientation ) {
        d->orientation = orientation ;
        this->updata() ;
    }
}

void Data::setOrientation( int angle ) {
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

inline Item* create_item( QSharedPointer<MToolbarItem> item ) {
    Item* new_item = new Item() ;

    if (item->alignment() == Qt::AlignLeft)
        new_item->setAlignment( Qt::AlignLeft | Qt::AlignVCenter ) ;
    else if (item->alignment() == Qt::AlignRight)
        new_item->setAlignment( Qt::AlignRight | Qt::AlignVCenter ) ;
    else
        new_item->setAlignment( Qt::AlignVCenter ) ;

    if ( !item->name().isEmpty() ) {
        new_item->setObjectName( item->name() );
    }

    if ( !item->iconId().isEmpty() ) {
        //qDebug() << "iconId : " << item->iconId() ;
        new_item->setIconId( item->iconId() ) ;
    } else {
        //qDebug() << "iconPath : " << item->icon() ;
        new_item->setIconPath( item->icon() ) ;
    }

    //if (!item->textId().isEmpty()) {
        //setText(qtTrId(itemPtr->textId().toUtf8().data()));
    //}
    //if (!itemPtr->text().isEmpty()) {
        //setText(itemPtr->text());
    //}

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

void Data::updata() {
    Q_D( Data ) ;
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
