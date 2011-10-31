#ifndef WIDGET_H
#define WIDGET_H

#include <QGraphicsWidget>
#include <QGraphicsItem>

class MAbstractInputMethodSettings ;

namespace widget {

class Widget : public QGraphicsWidget {
    Q_OBJECT
public :
    MAbstractInputMethodSettings* settings ;

    Widget( MAbstractInputMethodSettings* settings, QGraphicsItem* parent = 0 ) : QGraphicsWidget( parent ) {
        this->settings = settings ;
    }
} ;

}

#endif // WIDGET_H
