#ifndef ICON_H
#define ICON_H

#include <QDeclarativeItem>
#include <QPainter>

namespace toolbar {

class IconPrivate ;

class Icon : public QDeclarativeItem {
    Q_OBJECT
    Q_PROPERTY( QString iconId READ getIconId WRITE setIconId )
    Q_PROPERTY( QString iconPath READ getIconPath WRITE setIconPath )
public :
    explicit Icon( QDeclarativeItem* parent = 0 ) ;
    ~Icon() ;
    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0 ) ;

    const QString& getIconId() const ;
    void setIconId( const QString& iconId ) ;
    const QString& getIconPath() const ;
    void setIconPath( const QString& iconPath ) ;
public slots :
    //void setPath( const QString& path ) ;

private :
    Q_DISABLE_COPY( Icon ) ;
    Q_DECLARE_PRIVATE( Icon ) ;
    IconPrivate* d_ptr ;
} ;

}

#endif // ICON_H
