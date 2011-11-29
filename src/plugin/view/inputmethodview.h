#ifndef INPUTMETHOD_VIEW_H
#define INPUTMETHOD_VIEW_H

#include <mimgraphicsview.h>
#include <mabstractinputmethod.h>

namespace engine {
class Engine ;
}

namespace toolbar {
class ToolbarData ;
}

namespace inputmethod {

class InputMethodViewPrivate ;

class InputMethodView : public MImGraphicsView {
    Q_OBJECT

public :
    explicit InputMethodView( QWidget* mainWindow ) ;
    ~InputMethodView() ;
    void showContent() ;
    void hideContent() ;
    void load( const QString& path ) ;
    void setInputMethod( MAbstractInputMethod* inputmethod ) ;
    void setEngine( engine::Engine* engine ) ;
    void setToolbarData( toolbar::ToolbarData* toolbarData ) ;
    const QRect& screenRect( QWidget* widget = 0 ) ;

private :
    Q_DISABLE_COPY( InputMethodView ) ;
    Q_DECLARE_PRIVATE( InputMethodView ) ;
    InputMethodViewPrivate* d_ptr ;
} ;

}

#endif // INPUTMETHOD_VIEW_H
