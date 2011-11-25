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

    function sendCommit( text ) {
        var cursorPosition = textEdit.cursorPosition
        var head = textEdit.text.slice( 0, cursorPosition )
        var tail = textEdit.text.slice( cursorPosition, textEdit.text.length )
        textEdit.text = head.concat( text, tail )
        textEdit.cursorPosition = cursorPosition + text.length
    }

    function backspace() {
        var cursorPosition = textEdit.cursorPosition
        if ( cursorPosition > 0 ) {
            var head = textEdit.text.slice( 0, cursorPosition - 1 )
            var tail = textEdit.text.slice( cursorPosition, textEdit.text.length )
            textEdit.text = head.concat( tail )
            textEdit.cursorPosition = cursorPosition - 1
        }
    }

}

