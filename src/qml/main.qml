import QtQuick 1.1
import me.inputmethod 1.0
import me.inputmethod.toolbar 1.0
import me.utils.toucharea 1.0

Rectangle {
    id : canvas
    transformOrigin: Item.Center
    width : inputmethod.screenWidth
    height : inputmethod.screenHeight
    color : "transparent"

    Rectangle {
        id : root
        anchors.centerIn : parent
        transformOrigin: Item.Center
        width : canvas.width
        height : canvas.height
        color : "transparent"
        Rectangle {
            id : panel
            anchors.bottom : parent.bottom
            width : parent.width
            height : parent.height / 2
            color : "#FF00FF00"
            Toolbar {
                id : toolbar
                anchors.top : parent.top 
                anchors.horizontalCenter : parent.horizontalCenter
            }
            Button {
                id : testButton
                anchors.centerIn : parent
                width : parent.width / 2
                height : parent.height / 2
                /*color : "#FFFF0000"*/
            }
            Text {
                id : display
                anchors.centerIn : parent
                text : inputmethod.debugString
                font.pointSize: 16
                color : "white"
            }
        }
        RootTouchArea {
            anchors.fill : parent
            FakeTouchArea {
                id : testInput
                anchors.fill : parent
            }
        }
    }

    Component.onCompleted : {
        inputmethod.setInputMethodArea( Qt.rect( panel.x, panel.y, panel.width, panel.height ) )
        inputmethod.appOrientationChanged.connect( handleAppOrientationChanged )
        toolbarData.updated.connect( toolbar.update )
        testInput.entered.connect( testButton.handleEntered ) 
        testInput.exited.connect( testButton.handleExited ) 
    }

    function handleAppOrientationChanged( angle ) {
        root.rotation = angle
        if ( angle == 0 ) {
            root.width = canvas.width
            root.height = canvas.height
            var pos = root.mapToItem( canvas, panel.x, panel.y )
            /*display.text = "0\n" + pos.x + "," + pos.y + "," + panel.width + "," + panel.height + "\n" + inputmethod.debugString*/
            inputmethod.setInputMethodArea( Qt.rect( pos.x, pos.y, panel.width, panel.height ) )
        }
        else if ( angle == 270 ) {
            root.width = canvas.height
            root.height = canvas.width
            var pos = root.mapToItem( canvas, panel.x + panel.width, panel.y )
            /*display.text = "270\n" + pos.x + "," + pos.y + "," + panel.height + "," + panel.width + "\n" + inputmethod.debugString*/
            inputmethod.setInputMethodArea( Qt.rect( pos.x, pos.y, panel.height, panel.width ) )
        }
    }
}
