import QtQuick 1.1

BaseKey {
    property int keycode 
    /*property alias text : label.text*/
    height : keyboard.keyHeight
    width : keyboard.keyWidth
    Rectangle {
        id : bgRect
        anchors.fill : parent
        anchors.margins : 1
        color : "gray"
        Text {
            id : label
            text : keydata.keysym[keycode][0]
            anchors.centerIn : parent
            font.pixelSize : 26
            font.bold : true
            textFormat : Text.PlainText
            color : "white"
        }
    }

    states : [
        State {
            name : "PRESSED"
            when : ( pressed )
            PropertyChanges { target : bgRect ; color : "cornflowerblue" }
        }
    ]

    onPressed : {
        keyboard.processKeyEvent( 6, keycode, 0, label.text )
    }
    onReleased : {
        keyboard.processKeyEvent( 7, keycode, 0, label.text )
    }
}
