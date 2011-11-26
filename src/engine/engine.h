#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include <QObject>
#include <QKeyEvent>

namespace engine {

class EnginePrivate ;

class Engine : public QObject {
    Q_OBJECT

    Q_PROPERTY( bool active READ getActive WRITE setActive NOTIFY activeChanged ) 
    Q_PROPERTY( bool working READ getWorking NOTIFY workingChanged ) 
    
signals :
    void updated() ;
    void commit( QString text ) ;
    void activeChanged( bool working ) ;
    void workingChanged( bool working ) ;

public :
    explicit Engine( QObject* parent = 0 ) ;
    ~Engine() ;
    bool getActive() const ;
    void setActive( bool active ) ;
    bool getWorking() const ;
    void setWorking( bool working ) ;

public slots :
    void load( const QString& path ) ;
    void setFunctionKey( const QString& function, int key ) ;
    bool selectCandidate( int index ) ;
    bool processKeyEvent( QEvent::Type type, int keycode, Qt::KeyboardModifiers modifiers, const QString& text, bool autoRepeat, int count ) ;
    QString getCandidateString() ;

private :
    Q_DISABLE_COPY( Engine ) ;
    Q_DECLARE_PRIVATE( Engine ) ;
    EnginePrivate* d_ptr ;
} ;

}

#endif // ENGINE_ENGINE_H
