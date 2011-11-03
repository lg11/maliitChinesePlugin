#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QObject>
#include <QGraphicsWidget>
#include <QGraphicsItem>
#include <QGraphicsLinearLayout>

#include <mtoolbardata.h>
#include <mtoolbaritem.h>
#include <mwidget.h>

namespace toolbar {

class Toolbar : public MWidget {
    Q_OBJECT
public :
    QGraphicsLinearLayout* layout ;
    QGraphicsLinearLayout* left ;
    QGraphicsLinearLayout* right ;
    QGraphicsLinearLayout* center ;

    explicit Toolbar( QGraphicsItem* parent = 0 ) ;
    ~Toolbar() ;

    //void append( const QSharedPointer<MToolbarItem>& item ) ;
    void createWidget( const QSharedPointer<MToolbarItem> &item ) ;
    void set( QSharedPointer<const MToolbarData> toolbar, M::Orientation appOrientation ) ;
    void setWidth( qreal width ) ;
} ;

}

#endif // TOOLBAR_H
