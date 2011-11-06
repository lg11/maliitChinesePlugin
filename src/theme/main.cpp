#include <MApplication>
#include <MWindow>
#include <MButton>
#include <MTheme>
#include <mbuttonstyle.h>
#include <QDebug>

int main( int argc, char** argv ) {
    MApplication* app = new MApplication( argc, argv ) ;

    MWindow* win = new MWindow() ;
    //MButton* button = new MButton() ;

    const MStyle* style = MTheme::style( "MButtonStyle", QString(""), QString("active"), QString("default"), M::Landscape ) ;
    const MButtonStyle* buttonStyle = static_cast<const MButtonStyle*>(style) ;
    
    qDebug() << buttonStyle->iconSize() ;
    qDebug() << buttonStyle->font().pointSize() ;
    qDebug() << buttonStyle->font().pixelSize() ;
    
    win->showFullScreen() ;
    return app->exec() ;
}
