#ifndef TOOLBAR_DATA_H
#define TOOLBAR_DATA_H

#include <QObject>
#include <QDeclarativeListProperty>

#include <mtoolbardata.h>

#include "item.h"

namespace toolbar {

class DataPrivate ;

class Data : public QObject {
    Q_OBJECT
    Q_PROPERTY( QDeclarativeListProperty<toolbar::Item> items READ items )
public :
    explicit Data( QObject* parent = 0 ) ;
    ~Data() ;
    QDeclarativeListProperty<toolbar::Item> items() ;

signals :
    void updated() ;

public slots :
    void set( QSharedPointer<const MToolbarData> data ) ;
    void setOrientation( MInputMethod::Orientation orientation ) ;
    void setOrientation( int angle ) ;
    void updata() ;

private :
    Q_DISABLE_COPY( Data ) ;
    Q_DECLARE_PRIVATE( Data ) ;
    DataPrivate* d_ptr ;
} ;

}

#endif // TOOLBAR_DATA_H
