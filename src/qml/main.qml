import QtQuick 1.1
import me.utils.toucharea 1.0

/*import me.inputmethod 1.0*/
/*import me.inputmethod.toolbar 1.0*/


Rectangle {
    /*FakeInputMethod { id : inputmethod ; anchors.fill : parent }*/
    /*Engine { id : engine ; objectName : "engine" }*/
    id : canvas
    transformOrigin: Item.Center
    width : inputmethod.screenWidth
    height : inputmethod.screenHeight
    color : "transparent"

    Style { id : style }

    EditToolBar {}

    RootTouchArea {
        id : root
        anchors.centerIn : parent
        transformOrigin: Item.Center
        width : canvas.width
        height : canvas.height
        Rectangle {
            id : panel
            anchors.bottom : parent.bottom
            width : parent.width
            height : parent.height / 2
            color : "transparent"
            FullKeyboard {
                visible : false
                anchors.fill : parent
            }
            /*Toolbar {*/
                /*id : toolbar*/
                /*anchors.top : parent.top */
                /*anchors.horizontalCenter : parent.horizontalCenter*/
            /*}*/
        }
    }

    function handleAppOrientationChanged( angle ) {
        root.rotation = angle
        if ( angle == 0 ) {
            root.width = canvas.width
            root.height = canvas.height
            var pos = root.mapToItem( canvas, panel.x, panel.y )
            inputmethod.setInputMethodArea( Qt.rect( pos.x, pos.y, panel.width, panel.height ) )
        }
        else if ( angle == 270 ) {
            root.width = canvas.height
            root.height = canvas.width
            var pos = root.mapToItem( canvas, panel.x + panel.width, panel.y )
            inputmethod.setInputMethodArea( Qt.rect( pos.x, pos.y, panel.height, panel.width ) )
        }
    }

    Component.onCompleted : {
        inputmethod.setInputMethodArea( Qt.rect( 0, 0, 1, 1 ) )
        /*inputmethod.setInputMethodArea( Qt.rect( panel.x, panel.y, panel.width, panel.height ) )*/
        inputmethod.appOrientationChanged.connect( handleAppOrientationChanged )
        /*toolbarData.updated.connect( toolbar.update )*/
        console.log( "load start" )
        engine.load( "/opt/linputmethod/data/formated" )
        console.log( "load finish" )

        /*inputmethod.remapKey( Qt.Key_A, Qt.Key_Z )*/
        inputmethod.remapStickySymbol( "MASK_SHIFT", "a", "A" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "b", "B" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "c", "C" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "d", "D" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "e", "E" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "f", "F" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "g", "G" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "h", "H" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "i", "I" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "j", "J" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "k", "K" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "l", "L" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "m", "M" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "n", "N" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "o", "O" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "p", "P" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "q", "Q" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "r", "R" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "s", "S" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "t", "T" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "u", "U" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "v", "V" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "w", "W" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "x", "X" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "y", "Y" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "z", "Z" )
        
        inputmethod.remapStickySymbol( "MASK_SHIFT", ",", ";" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", ".", ":" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "'", "*" )
        inputmethod.remapStickySymbol( "MASK_SHIFT", "@", "/" )

        inputmethod.remapStickySymbol( "MASK_FN", "a", "!" )
        inputmethod.remapStickySymbol( "MASK_FN", "b", ">" )
        inputmethod.remapStickySymbol( "MASK_FN", "c", "|" )
        inputmethod.remapStickySymbol( "MASK_FN", "d", "&" )
        inputmethod.remapStickySymbol( "MASK_FN", "e", "3" )
        inputmethod.remapStickySymbol( "MASK_FN", "f", "(" )
        inputmethod.remapStickySymbol( "MASK_FN", "g", ")" )
        inputmethod.remapStickySymbol( "MASK_FN", "h", "_" )
        inputmethod.remapStickySymbol( "MASK_FN", "i", "8" )
        inputmethod.remapStickySymbol( "MASK_FN", "j", "-" )
        inputmethod.remapStickySymbol( "MASK_FN", "k", "+" )
        inputmethod.remapStickySymbol( "MASK_FN", "l", "#" )
        inputmethod.remapStickySymbol( "MASK_FN", "m", "=" )
        inputmethod.remapStickySymbol( "MASK_FN", "n", "%" )
        inputmethod.remapStickySymbol( "MASK_FN", "o", "9" )
        inputmethod.remapStickySymbol( "MASK_FN", "p", "0" )
        inputmethod.remapStickySymbol( "MASK_FN", "q", "1" )
        inputmethod.remapStickySymbol( "MASK_FN", "r", "4" )
        inputmethod.remapStickySymbol( "MASK_FN", "s", "\"" )
        inputmethod.remapStickySymbol( "MASK_FN", "t", "5" )
        inputmethod.remapStickySymbol( "MASK_FN", "u", "7" )
        inputmethod.remapStickySymbol( "MASK_FN", "v", "<" )
        inputmethod.remapStickySymbol( "MASK_FN", "w", "2" )
        inputmethod.remapStickySymbol( "MASK_FN", "x", "$" )
        inputmethod.remapStickySymbol( "MASK_FN", "y", "6" )
        inputmethod.remapStickySymbol( "MASK_FN", "z", "~" )
        
        inputmethod.remapStickySymbol( "MASK_FN", ",", ";" )
        inputmethod.remapStickySymbol( "MASK_FN", ".", ":" )
        inputmethod.remapStickySymbol( "MASK_FN", "'", "*" )
        inputmethod.remapStickySymbol( "MASK_FN", "@", "/" )

        inputmethod.remapSymbol( "€", "|" )
        inputmethod.remapSymbol( "£", "~" )

        engine.remapPunc( ",", "，" )
        engine.remapPunc( ".", "。" )
        engine.remapPunc( "!", "！" )
        engine.remapPunc( "?", "？" )
        engine.remapPunc( ":", "：" )
        engine.remapPunc( ";", "；" )
        engine.remapPunc( "'", "‘" )
        engine.remapPunc( "\"", "“" )

        /*engine.setFunctionKey( "CANDIDATE_1", Qt.Key_Space )*/
        /*engine.setFunctionKey( "CANDIDATE_2", Qt.Key_Question )*/
        /*engine.setFunctionKey( "CANDIDATE_3", Qt.Key_Left )*/
        /*engine.setFunctionKey( "CANDIDATE_4", Qt.Key_Down )*/
        /*engine.setFunctionKey( "CANDIDATE_5", Qt.Key_Right )*/
        /*engine.setFunctionKey( "NEXT_PAGE", Qt.Key_Period )*/
        /*engine.setFunctionKey( "PREV_PAGE", Qt.Key_Comma )*/

        console.log( inputmethod.screenWidth, inputmethod.screenHeight )

        engine.commit.connect( inputmethod.sendCommit )
    }

}
