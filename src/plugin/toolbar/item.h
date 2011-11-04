#ifndef ITEM_H
#define ITEM_H

#include <QObject>

namespace toolbar {

class ItemPrivate ;

class Item : public QObject {
    Q_OBJECT
    Q_PROPERTY( QString text READ getText WRITE setText NOTIFY textChanged )

signals :
    void textChanged( const QString& text ) ;

public :
    explicit Item( QObject* parent = 0 ) ;
    ~Item() ;

    const QString& getText() ;
    void setText( const QString& text ) ;
private :
    Q_DISABLE_COPY( Item ) ;
    Q_DECLARE_PRIVATE( Item ) ;
    ItemPrivate* const d_ptr ;
} ;

}

#endif // ITEM_H
