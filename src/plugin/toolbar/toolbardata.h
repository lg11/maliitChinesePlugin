#ifndef TOOLBARDATA_H
#define TOOLBARDATA_H

#include <QObject>
#include <QDeclarativeListProperty>

#include <mtoolbardata.h>

#include "toolbaritem.h"

namespace toolbar {

class ToolbarDataPrivate ;

class ToolbarData : public QObject {
    Q_OBJECT
    Q_PROPERTY( QDeclarativeListProperty<toolbar::ToolbarItem> items READ items )
public :
    explicit ToolbarData( QObject* parent = 0 ) ;
    ~ToolbarData() ;
    QDeclarativeListProperty<toolbar::ToolbarItem> items() ;

signals :
    void updated() ;

public slots :
    void set( QSharedPointer<const MToolbarData> data ) ;
    void setOrientation( MInputMethod::Orientation orientation ) ;
    void setOrientation( int angle ) ;
    void updata() ;

private :
    Q_DISABLE_COPY( ToolbarData ) ;
    Q_DECLARE_PRIVATE( ToolbarData ) ;
    ToolbarDataPrivate* d_ptr ;
} ;

}

#endif // TOOLBARDATA_H
