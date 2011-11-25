#ifndef KEYFILTER_H
#define KEYFILTER_H

#include <QObject>
#include <QKeyEvent>

namespace engine {

class KeyFilterPrivate ;

class KeyFilter {
public :
    KeyFilter() ;
    ~KeyFilter() ;
    bool filter( QEvent::Type keyType, Qt::Key keyCode, Qt::KeyboardModifiers modifiers, const QString& text, bool autoRepeat, int count ) ;
private :
    Q_DECLARE_PRIVATE( KeyFilter ) ;
    KeyFilterPrivate* d_ptr ;
} ;

}

#endif // KEYFILTER_H
