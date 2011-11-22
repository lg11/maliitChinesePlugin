import QtQuick 1.1

QtObject {
    property QtObject key : QtObject {
        property Item label : Text {
            font.pixelSize : 24
        }
        property color bgColor : "Gray"
    }
}
