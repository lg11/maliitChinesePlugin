#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <mabstractinputmethodsettings.h>
#include <MGConfItem>

namespace settings {

class Settings : public QObject, public MAbstractInputMethodSettings {
    Q_OBJECT

public :
    MGConfItem enabledKeyboardsConf ;

    explicit Settings() ;
    ~Settings() ;

    virtual QString title() ;
    virtual QString icon() ;
    virtual QGraphicsWidget *createContentWidget( QGraphicsWidget *parent = 0 ) ;

    QStringList selectedKeyboards() const ;

public slots :
    void slotEnabledKeyboardsChanged() ;

signals :
    //! Emiited when selected keyboards are changed.
    void enabledKeyboardsChanged() ;
} ;

}

#endif // SETTINGS_H
