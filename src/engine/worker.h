#ifndef ENGINE_WORKER_H
#define ENGINE_WORKER_H

#include <QObject>
#include <QPair>
#include <QList>
#include <QString>
#include <QFile>
#include <QTimer>
#include <QTextStream>

namespace lookup {
class Lookup ;
}

namespace t9 {
class T9Lookup ;
}

namespace engine {

typedef QPair<const QString*, const QString*> KeyPair ;
typedef QPair<const QString*, qreal > WordPair ;
typedef QPair<KeyPair, WordPair> CandPair ;
typedef QPair<CandPair, int> Candidate ;

typedef QPair<QString, QString> SelectedKeyPair ;
typedef QPair< QString, QList<qreal> > SelectedWordPair ;
typedef QPair<SelectedKeyPair, SelectedWordPair> SelectedPair ;

class Worker {
public:
    //Q_ENUMS( KeyboardLayout )
    enum KeyboardLayout { UnknownKeyboardLayout = 0, FullKeyboardLayout = 1, T9KeyboardLayout = 2 } ;

    lookup::Lookup* lookup ;
    t9::T9Lookup* t9lookup ;
    SelectedPair selected ;
    QString* selectedWord ;
    int pageStartIndex ;
    const Candidate* candidate ;
    KeyboardLayout keyboardLayout ;
    //QFile* logFile ;
    //QTextStream* textStream ;
    //QTimer flushTimer ;

    Worker() ;

    ~Worker() ;

    //void startLog( const QString& path ) ;

    //void stopLog() ;

    //void flushLog() ;
    
    void load( const QString& path ) ;
    
    bool prevPage( int pageLength ) ;
    
    bool nextPage( int pageLength ) ;
    
    int getCodeLength() const ;
    
    int getPreeditCodeLength() const ;
    
    int getInvalidCodeLength() const ;

    int getSelectedWordLength() const ;
   
    bool updateCandidate( int index ) ;
    
    QString getCode() const ;

    QString getWord() const ;
    
    QString getPreeditCode() const ;

    QString getInvalidCode() const ;

    QString getSelectedWord() const ;

    //bool checkCommit() ;

    bool select( int index ) ;

    bool deselect() ;

    void reset() ;

    bool appendCode( QChar code ) ;

    //bool appendCode( const QString& code ) ;

    bool popCode() ;

    void commit() ;

    bool setKeyboardLayout( KeyboardLayout layout ) ;

    //bool setKeyboardLayout( int layout ) ;

} ;

}

#endif // ENGINE_WORKER_H

