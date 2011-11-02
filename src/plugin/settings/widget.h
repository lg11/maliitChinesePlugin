#ifndef WIDGET_H
#define WIDGET_H

#include <QGraphicsWidget>
#include <QGraphicsItem>

class MAbstractInputMethodSettings ;

namespace settings {

class Widget : public QGraphicsWidget {
    Q_OBJECT
public :
    MAbstractInputMethodSettings* settings ;

    explicit Widget( MAbstractInputMethodSettings* settings, QGraphicsItem* parent = 0 ) : QGraphicsWidget( parent ) {
        this->settings = settings ;
    }
} ;

}

#endif // WIDGET_H
