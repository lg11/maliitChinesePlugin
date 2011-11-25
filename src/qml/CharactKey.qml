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
            font.pixelSize : 22
            font.bold : true
            textFormat : Text.PlainText
            color : "white"
        }
    }

    states : [
        State {
            name : "PRESSED"
            when : ( pressed )
            PropertyChanges { target : bgRect ; color : "blue" }
        }
    ]

    onReleased : {
        keyboard.processKeyEvent( keycode, 0 )
    }
}
