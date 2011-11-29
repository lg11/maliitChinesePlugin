import QtQuick 1.1
import me.inputmethod.toolbar 1.0
import me.utils.toucharea 1.0

BaseKey {
    property alias iconId : icon.iconId
    property alias iconPath : icon.iconPath
    property alias text : label.text
    property real sizePercent : 1.0
    height : toolbar.height
    width : text.length <= 0 ? height : label.paintedWidth
    
    ToolbarIcon {
        id : icon
        anchors.centerIn : parent
        height : paintedHeight > parent.height ? parent.height * parent.sizePercent : paintedHeight * parent.sizePercent
        width : paintedHeight > parent.height ? parent.height * parent.sizePercent * paintedWidth / paintedHeight : paintedWidth * sizePercent
    }

    Text {
        id : label
        anchors.centerIn : parent
        font.pixelSize : 22
    }

    /*FakeTouchArea {*/
        /*id : input*/
        /*anchors.fill : parent*/
    /*}*/
    
    Component.onCompleted : {
        /*input.entered.connect( handleEntered )*/
        /*input.exited.connect( handleExited )*/
        /*input.released.connect( handleReleased )*/
    }
}
