#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsLinearLayout>
#include <MWidget>
#include <MToolbarItem>

namespace toolbar {

class Toolbar : public MWidget {
    Q_OBJECT
public :
    QGraphicsLinearLayout* layout ;

    explicit Toolbar( QGraphicsItem* parent = 0 ) ;
    ~Toolbar() ;

    void appendItem( const QSharedPointer<MToolbarItem>& item ) ;
} ;

}

#endif // TOOLBAR_H
