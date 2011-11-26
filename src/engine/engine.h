#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include <QObject>
#include <QKeyEvent>

namespace engine {

class EnginePrivate ;

class Engine : public QObject {
    Q_OBJECT
    
signals :
    void updated() ;
    void commit( QString text ) ;

public :
    explicit Engine( QObject* parent = 0 ) ;
    ~Engine() ;

public slots :
    void load( const QString& path ) ;
    bool processKeyEvent( QEvent::Type type, int keycode, Qt::KeyboardModifiers modifiers, const QString& text, bool autoRepeat, int count ) ;
    QString getCandidateString() ;
private :
    Q_DISABLE_COPY( Engine ) ;
    Q_DECLARE_PRIVATE( Engine ) ;
    EnginePrivate* d_ptr ;
} ;

}

#endif // ENGINE_ENGINE_H
