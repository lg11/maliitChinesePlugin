import QtQuick 1.1
import me.inputmethod.toolbar 1.0

BaseButton {
    property alias iconId : icon.iconId
    property alias iconPath : icon.iconPath
    property alias text : label.text
    property real sizePercent : 1.0
    height : toolbar.height - 8
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
}
