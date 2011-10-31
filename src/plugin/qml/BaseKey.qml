import QtQuick 1.1
/*import Qt.labs.gestures 1.0*/

FakeMouseArea {
    id : key
    property bool keepDown : false 
    property alias checked : button.checked
    property alias text : button.text

    Rectangle {
        id : button
        property bool checked : down || keepDown
        property string text
        x : 2
        y : 2
        width : parent.width - 4
        height : parent.height - 4
        /*anchors.centerIn :parent*/
        states {
            State {
            }
        }
    }
}
