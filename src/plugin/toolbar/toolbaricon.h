#ifndef TOOLBARICON_H
#define TOOLBARICON_H

#include <QDeclarativeItem>
#include <QPainter>

namespace toolbar {

class ToolbarIconPrivate ;

class ToolbarIcon : public QDeclarativeItem {
    Q_OBJECT
    Q_PROPERTY( QString iconId READ getIconId WRITE setIconId )
    Q_PROPERTY( QString iconPath READ getIconPath WRITE setIconPath )
    Q_PROPERTY( qreal paintedWidth READ getPaintedWidth NOTIFY paintedWidthChanged )
    Q_PROPERTY( qreal paintedHeight READ getPaintedHeight NOTIFY paintedHeightChanged )

signals :
    void paintedWidthChanged( qreal paintedWidth ) ;
    void paintedHeightChanged( qreal paintedHeight ) ;
public :
    explicit ToolbarIcon( QDeclarativeItem* parent = 0 ) ;
    ~ToolbarIcon() ;
    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0 ) ;

    void checkPaintedSize() ;
    const QString& getIconId() const ;
    void setIconId( const QString& iconId ) ;
    const QString& getIconPath() const ;
    void setIconPath( const QString& iconPath ) ;
    qreal getPaintedWidth() const ;
    qreal getPaintedHeight() const ;

private :
    Q_DISABLE_COPY( ToolbarIcon ) ;
    Q_DECLARE_PRIVATE( ToolbarIcon ) ;
    ToolbarIconPrivate* d_ptr ;
} ;

}

#endif // TOOLBARICON_H
