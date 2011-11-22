import QtQuick 1.1

BaseKey {
    property alias text : label.text
    Rectangle {
        id : bgRect
        anchors.fill : parent
        anchors.margins : 1
        color : "gray"
        Text {
            id : label
            anchors.centerIn : parent
            font.pixelSize : 22
            font.bold : true
            textFormat : Text.PlainText
            color : "white"
        }
    }
    width : 480 / 10
    height : 400 / 4

    states : [
        State {
            name : "PRESSED"
            when : ( pressed )
            PropertyChanges { target : bgRect ; color : "blue" }
        }
    ]
}
