import QtQuick 1.1

Item {
    property bool pressed : false
    property int padding : 0
    property alias color : plat.color

    Rectangle {
        id : plat
        anchors.centerIn : parent
        width : parent.width - padding * 2
        height : parent.height - padding * 2
        color : "#FF444444"
    }

    function handleEntered() {
        console.log( "enter" )
        pressed = true
    }
    function handleExited() {
        console.log( "exit" )
        pressed = false
    }

    states : [
        State {
            name : "PRESSED"
            when : ( pressed )
            PropertyChanges { target : plat ; color : "blue" }
        }
    ]
    
}

