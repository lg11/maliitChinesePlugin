import QtQuick 1.1
/*import me.inputmethod 1.0*/
/*import me.inputmethod.toolbar 1.0*/

Item {
    width : parent.width
    height : 56

    Component {
        id : buttonComponent
        ToolbarButton {
        }
    }
    Rectangle {
        id : background
        anchors.fill : parent
        color : "gray"
    }
    Row {
        id : leftRow
        anchors.verticalCenter : parent.verticalCenter
        anchors.left : parent.left
    }
    Row {
        id : centerRow
        anchors.centerIn : parent
    }
    Row {
        id : rightRow
        anchors.verticalCenter : parent.verticalCenter
        anchors.right : parent.right
        /*layoutDirection : Qt.RightToLeft*/
    }

    function clear() {
        var l
        l = leftRow.children.length
        for ( var i = 0 ; i < l ; i++ ) {
            var obj = leftRow.children[i]
            obj.destroy( 1 )
        }
        l = centerRow.children.length
        for ( var i = 0 ; i < l ; i++ ) {
            var obj = centerRow.children[i]
            obj.destroy( 1 )
        }
        l = rightRow.children.length
        for ( var i = 0 ; i < l ; i++ ) {
            var obj = rightRow.children[i]
            obj.destroy( 1 )
        }
    }

    function setButton( button, item ) {
        button.iconId = item.iconId
        button.iconPath = item.iconPath
        button.text = item.text
        button.sizePercent = item.size / 100.00
    }

    function update() {
        clear()
        var l = toolbarData.items.length
        for ( var i = 0 ; i < l ; i++ ) {
            var item = toolbarData.items[i]
            var button
            if ( item.alignment == Qt.AlignLeft ) {
                console.log( "left" )
                button = buttonComponent.createObject( leftRow, { padding : 8 } )
                setButton( button, item )
            }
            else if ( item.alignment == Qt.AlignRight ) {
                console.log( "right" )
                button = buttonComponent.createObject( rightRow, {} )
                setButton( button, item )
            }
            else {
                console.log( "center" )
                button = buttonComponent.createObject( centerRow, {} )
                setButton( button, item )
            }
        }
        console.log( "toobar update", leftRow.children.length )
    }
}
