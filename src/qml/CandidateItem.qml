import QtQuick 1.1

Rectangle {
    property alias text : label.text
    visible : text.length > 0
    color : "gray"
    height : label.paintedHeight + 4
    width : label.paintedWidth + 8
    Text {
        id : label
        color : "white"
        anchors.centerIn : parent
        onTextChanged : {
            console.log( text )
        }
    }
}
