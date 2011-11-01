#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QObject>
#include <QGraphicsItem>
#include <MWidget>

namespace toolbar {

class Toolbar : public MWidget {
    Q_OBJECT
public :
    explicit Toolbar( QGraphicsItem* parent = 0 ) ;
    ~Toolbar() ;
} ;

}

#endif // TOOLBAR_H
