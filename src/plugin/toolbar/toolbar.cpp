#include "toolbar.h"
#include "button.h"

#include <mtoolbarlayout.h>
#include <mlabel.h>

#include <QDebug>

namespace toolbar {

Toolbar::Toolbar( QGraphicsItem* parent ) : \
    MWidget( parent ), \
    layout( new QGraphicsLinearLayout( Qt::Horizontal, this ) ), \
    left( new QGraphicsLinearLayout( Qt::Horizontal, this->layout ) ), \
    right( new QGraphicsLinearLayout( Qt::Horizontal, this->layout ) ), \
    center( new QGraphicsLinearLayout( Qt::Horizontal, this->layout ) ) \
{
    this->layout->addItem( this->left ) ;
    this->layout->addStretch() ;
    this->layout->addItem( this->center ) ;
    this->layout->addStretch() ;
    this->layout->addItem( this->right ) ;

    this->layout->setAlignment( this->left, Qt::AlignLeft | Qt::AlignVCenter ) ;
    this->layout->setAlignment( this->center, Qt::AlignHCenter | Qt::AlignVCenter ) ;
    this->layout->setAlignment( this->right, Qt::AlignRight | Qt::AlignVCenter ) ;

    this->left->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::Fixed ) ;
    this->right->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::Fixed ) ;
    this->center->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::Fixed ) ;

    this->setLayout( this->layout ) ;

    this->layout->setSpacing( 0 ) ;
    this->layout->setContentsMargins( 0, 0, 0, 0 ) ;
    this->left->setSpacing( 0 ) ;
    this->left->setContentsMargins( 0, 0, 0, 0 ) ;
    this->right->setSpacing( 0 ) ;
    this->right->setContentsMargins( 0, 0, 0, 0 ) ;
    this->center->setSpacing( 0 ) ;
    this->center->setContentsMargins( 0, 0, 0, 0 ) ;

    this->center->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed ) ;
}

Toolbar::~Toolbar() {}

//void Toolbar::appendItem( const QSharedPointer<MToolbarItem>& item ) {
//}

void Toolbar::createWidget( const QSharedPointer<MToolbarItem> &item ) {
    MWidget* widget = 0;
    //WidgetBar *sidebar = 0;

    //if (item->alignment() == Qt::AlignLeft) {

    if ( item->type() == MInputMethod::ItemButton ) {
        widget = new Button( this, item ) ;
    }
    else if ( item->type() == MInputMethod::ItemLabel ) {
        widget = new MLabel( item->text(), this ) ;
    }
    else
        return ;

    QGraphicsLinearLayout* layout ;
    if ( item->alignment() == Qt::AlignLeft )
        layout = this->left ;
    else if ( item->alignment() == Qt::AlignRight )
        layout = this->right ;
    else
        layout = this->center ;

    layout->addItem( widget ) ;
    layout->setAlignment( widget, Qt::AlignVCenter) ;


        //connect(widget, SIGNAL(clicked(MToolbarItem*)),
                //this, SLOT(handleButtonClick(MToolbarItem*)));
    //} else {
        //widget = new MToolbarLabel(item, sidebar);
    //}
    //customWidgets.append(widget);
    //// We should update the reaction map if the custom toolbar elements are changing.
    //connect(widget, SIGNAL(geometryChanged()),
            //&signalForwarder, SIGNAL(requestRepaint()), Qt::UniqueConnection);
    //connect(widget, SIGNAL(displayEntered()),
            //&signalForwarder, SIGNAL(requestRepaint()), Qt::UniqueConnection);
    //connect(widget, SIGNAL(displayExited()),
            //&signalForwarder, SIGNAL(requestRepaint()), Qt::UniqueConnection);
    //if (sidebar->count() == 0) {
        //// must be done before appending so that isVisible() tells the truth
        //sidebar->show();
    //}
    //sidebar->append(widget, item->isVisible());
}

void Toolbar::set( QSharedPointer<const MToolbarData> toolbar, M::Orientation appOrientation ) {
    QSharedPointer<const MToolbarLayout> layout = toolbar->layout( static_cast<MInputMethod::Orientation>(appOrientation) ) ;

    if ( layout.isNull() ) {
        return;
    }

    //this->center->addStretch() ;
    foreach( QSharedPointer<MToolbarItem> item, layout->items() ) {
        this->createWidget( item ) ;
    }
    //this->left->addStretch() ;
    //this->right->addStretch() ;
    //this->center->addStretch() ;
}

void Toolbar::setWidth( qreal width ) {
    this->resize( width, 40 ) ;
}

}
