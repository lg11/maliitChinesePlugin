#ifndef TOOLBARITEM_H
#define TOOLBARITEM_H\

#include <QObject>

namespace toolbar {

class ToolbarItemPrivate ;

class ToolbarItem : public QObject {
    Q_OBJECT
    Q_PROPERTY( QString text READ getText WRITE setText NOTIFY textChanged )
    Q_PROPERTY( QString iconId READ getIconId WRITE setIconId NOTIFY iconIdChanged )
    Q_PROPERTY( QString iconPath READ getIconPath WRITE setIconPath NOTIFY iconPathChanged )
    Q_PROPERTY( int size READ getSize WRITE setSize NOTIFY sizeChanged )
    Q_PROPERTY( Qt::Alignment alignment READ getAlignment WRITE setAlignment NOTIFY alignmentChanged )

signals :
    void textChanged( const QString& text ) ;
    void iconIdChanged( const QString& iconId ) ;
    void iconPathChanged( const QString& iconPath ) ;
    void sizeChanged( int size ) ;
    void alignmentChanged( Qt::Alignment ) ;

public :
    explicit ToolbarItem( QObject* parent = 0 ) ;
    ~ToolbarItem() ;

    const QString& getText() const ;
    void setText( const QString& text ) ;
    const QString& getIconId() const ;
    void setIconId( const QString& iconId ) ;
    const QString& getIconPath() const ;
    void setIconPath( const QString& iconPath ) ;
    int getSize() const ;
    void setSize( int size ) ;
    Qt::Alignment getAlignment() const ;
    void setAlignment( Qt::Alignment alignment ) ;

private :
    Q_DISABLE_COPY( ToolbarItem ) ;
    Q_DECLARE_PRIVATE( ToolbarItem ) ;
    ToolbarItemPrivate* const d_ptr ;
} ;

}

#endif // TOOLBARITEM_H
