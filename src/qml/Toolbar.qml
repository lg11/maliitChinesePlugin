import QtQuick 1.1
/*import me.inputmethod 1.0*/
/*import me.inputmethod.toolbar 1.0*/

Item {
    width : parent.width
    height : 56

    Component {
        id : buttonComponent
        Button {
            height : 48
            width : 48
        }
    }
    Rectangle {
        id : background
        anchors.fill : parent
        color : "gray"
    }
    Row {
        id : leftRow
        spacing : 4
        anchors.verticalCenter : parent.verticalCenter
        anchors.left : parent.left
    }
    Row {
        id : centerRow
        spacing : 4
        anchors.verticalCenter : parent.verticalCenter
        anchors.centerIn : parent
    }
    Row {
        id : rightRow
        spacing : 4
        anchors.verticalCenter : parent.verticalCenter
        anchors.right : parent.right
        layoutDirection : Qt.RightToLeft
    }

    function clear() {
        var l = leftRow.children.length
        for ( var i = 0 ; i < l ; i++ ) {
            var obj = leftRow.children[i]
            obj.destroy( 1 )
        }
    }
    function update() {
        clear()
        var l = toolbarData.items.length
        for ( var i = 0 ; i < l ; i++ ) {
            var item = toolbarData.items[i]
            /*if item*/
            var button = buttonComponent.createObject( leftRow, {} )
        }
        console.log( "toobar update", leftRow.children.length )
    }
}
