#ifndef BUTTON_H
#define BUTTON_H

#include <MButton>
#include <QSharedPointer>

class QPixmap;
class MToolbarItem;
class MToolbarButtonView;

namespace toolbar {

class ButtonPrivate ;

class Button : public MButton {
    Q_OBJECT

public :
    explicit Button( QGraphicsItem *parent, QSharedPointer<MToolbarItem> item ) ;
    virtual ~Button() ;
    void setIconFile( const QString& path ) ;
private :
    Q_DECLARE_PRIVATE( Button ) ;
    ButtonPrivate* const d_ptr ;
} ;

}

#endif // BUTTON_H
