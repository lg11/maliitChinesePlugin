#ifndef ITEM_H
#define ITEM_H

#include <QObject>

namespace toolbar {

class ItemPrivate ;

class Item : public QObject {
    Q_OBJECT
    Q_PROPERTY( QString text READ getText WRITE setText NOTIFY textChanged )
    Q_PROPERTY( Qt::Alignment alignment READ getAlignment WRITE setAlignment NOTIFY alignmentChanged )

signals :
    void textChanged( const QString& text ) ;
    void alignmentChanged( Qt::Alignment ) ;

public :
    explicit Item( QObject* parent = 0 ) ;
    ~Item() ;

    const QString& getText() const ;
    void setText( const QString& text ) ;
    Qt::Alignment getAlignment() const ;
    void setAlignment( Qt::Alignment alignment ) ;

private :
    Q_DISABLE_COPY( Item ) ;
    Q_DECLARE_PRIVATE( Item ) ;
    ItemPrivate* const d_ptr ;
} ;

}

#endif // ITEM_H
