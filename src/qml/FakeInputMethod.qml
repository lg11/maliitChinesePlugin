import QtQuick 1.1

Item {
    id : inputmethod
    property int screenWidth : 480
    property int screenHeight : 854
    property string debugString : ""
    function setInputMethodArea( rect ) {}
    signal appOrientationChanged( int angle )
    signal cursorRectChanged( variant cursorRect )

    TextEdit {
        id : textEdit
        anchors.top : parent.top
        anchors.horizontalCenter : parent.horizontalCenter
        width : parent.width
        height : parent.height / 2
        onCursorRectangleChanged : { inputmethod.cursorRectChanged( cursorRectangle ) }
        font.pixelSize : 22
        textFormat : TextEdit.PlainText
        wrapMode : TextEdit.WordWrap
        /*activeFocusOnPress : false*/
    }

}

