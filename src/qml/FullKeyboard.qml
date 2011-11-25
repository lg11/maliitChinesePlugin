import QtQuick 1.1

Item {
    id : keyboard
    focus: true

    property QtObject keydata : KeyData {}
    property int keyWidth : width / 10
    property int keyHeight : height / 5
    Column {
        Row {
            CharactKey { keycode : Qt.Key_Q }
            CharactKey { keycode : Qt.Key_W }
            CharactKey { keycode : Qt.Key_E }
            CharactKey { keycode : Qt.Key_R }
            CharactKey { keycode : Qt.Key_T }
            CharactKey { keycode : Qt.Key_Y }
            CharactKey { keycode : Qt.Key_U }
            CharactKey { keycode : Qt.Key_I }
            CharactKey { keycode : Qt.Key_O }
            CharactKey { keycode : Qt.Key_P }
        }
        Row {
            Item { height : 1 ; width : keyWidth * 0.5 }
            CharactKey { keycode : Qt.Key_A }
            CharactKey { keycode : Qt.Key_S }
            CharactKey { keycode : Qt.Key_D }
            CharactKey { keycode : Qt.Key_F }
            CharactKey { keycode : Qt.Key_G }
            CharactKey { keycode : Qt.Key_H }
            CharactKey { keycode : Qt.Key_J }
            CharactKey { keycode : Qt.Key_K }
            CharactKey { keycode : Qt.Key_L }
        }
        Row {
            Item { height : 1 ; width : keyWidth * 0.85 }
            CharactKey { keycode : Qt.Key_Z }
            CharactKey { keycode : Qt.Key_X }
            CharactKey { keycode : Qt.Key_C }
            CharactKey { keycode : Qt.Key_V }
            CharactKey { keycode : Qt.Key_B }
            CharactKey { keycode : Qt.Key_N }
            CharactKey { keycode : Qt.Key_M }
            FunctionKey { keycode : Qt.Key_Backspace ; width : keyWidth * 2.15 }
        }
        Row {
            FunctionKey { keycode : Qt.Key_Shift ; width : keyWidth * 1.75 }
            FunctionKey { keycode : Qt.Key_Alt ; width : keyWidth * 1.75 }
            FunctionKey { keycode : Qt.Key_Space ; width : keyWidth * 3 }
            FunctionKey { keycode : Qt.Key_Alt ; width : keyWidth * 1.75 }
            FunctionKey { keycode : Qt.Key_Shift ; width : keyWidth * 1.75 }
        }
    }

    Keys.onPressed : {
        event.accepted = processKeyEvent( event.key, event.modifiers )
    }

    function processKeyEvent( keycode, modifiers ) {
        var flag = engine.processKeyEvent( keycode )
        if ( !flag ) {
            if ( keycode == Qt.Key_Backspace )
                inputmethod.backspace()
        }
        return flag
    }
}
