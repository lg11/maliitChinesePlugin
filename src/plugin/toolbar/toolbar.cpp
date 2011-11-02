#include "toolbar.h"


namespace toolbar {

Toolbar::Toolbar( QGraphicsItem* parent ) : MWidget( parent ), layout( new QGraphicsLinearLayout( Qt::Horizontal, this ) ) {
}

Toolbar::~Toolbar() {}

void Toolbar::appendItem( const QSharedPointer<MToolbarItem>& item ) {
}

}
