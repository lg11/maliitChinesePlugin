import QtQuick 1.1
import me.utils.toucharea 1.0

/*import me.inputmethod 1.0*/
/*import me.inputmethod.toolbar 1.0*/


Rectangle {
    FakeInputMethod { id : inputmethod ; anchors.fill : parent }
    id : canvas
    transformOrigin: Item.Center
    width : inputmethod.screenWidth
    height : inputmethod.screenHeight
    color : "transparent"

    Style { id : style }
    Engine { id : engine }

    EditToolBar {}

    RootTouchArea {
        id : root
        anchors.centerIn : parent
        transformOrigin: Item.Center
        width : canvas.width
        height : canvas.height
        Rectangle {
            id : panel
            anchors.bottom : parent.bottom
            width : parent.width
            height : parent.height / 2
            color : "white"
            FullKeyboard {
                anchors.fill : parent
            }
            /*Toolbar {*/
                /*id : toolbar*/
                /*anchors.top : parent.top */
                /*anchors.horizontalCenter : parent.horizontalCenter*/
            /*}*/
        }
    }

    function handleAppOrientationChanged( angle ) {
        root.rotation = angle
        if ( angle == 0 ) {
            root.width = canvas.width
            root.height = canvas.height
            var pos = root.mapToItem( canvas, panel.x, panel.y )
            inputmethod.setInputMethodArea( Qt.rect( pos.x, pos.y, panel.width, panel.height ) )
        }
        else if ( angle == 270 ) {
            root.width = canvas.height
            root.height = canvas.width
            var pos = root.mapToItem( canvas, panel.x + panel.width, panel.y )
            inputmethod.setInputMethodArea( Qt.rect( pos.x, pos.y, panel.height, panel.width ) )
        }
    }

    Component.onCompleted : {
        inputmethod.setInputMethodArea( Qt.rect( panel.x, panel.y, panel.width, panel.height ) )
        inputmethod.appOrientationChanged.connect( handleAppOrientationChanged )
        /*toolbarData.updated.connect( toolbar.update )*/
        console.log( "load start" )
        engine.load( "../../data/formated" )
        console.log( "load finish" )
    }

}
