import QtQuick 1.1

Item {
    id : keyboard
    focus: true

    property QtObject keydata : KeyData {}
    Column {
        Row {
            Key { keycode : Qt.Key_Q }
            Key { keycode : Qt.Key_W }
            Key { keycode : Qt.Key_E }
            Key { keycode : Qt.Key_R }
            Key { keycode : Qt.Key_T }
            Key { keycode : Qt.Key_Y }
            Key { keycode : Qt.Key_U }
            Key { keycode : Qt.Key_I }
            Key { keycode : Qt.Key_O }
            Key { keycode : Qt.Key_P }
        }
        Row {
            Key { keycode : Qt.Key_A }
            Key { keycode : Qt.Key_S }
            Key { keycode : Qt.Key_D }
            Key { keycode : Qt.Key_F }
            Key { keycode : Qt.Key_G }
            Key { keycode : Qt.Key_H }
            Key { keycode : Qt.Key_J }
            Key { keycode : Qt.Key_K }
            Key { keycode : Qt.Key_L }
        }
        Row {
            Key { keycode : Qt.Key_Z }
            Key { keycode : Qt.Key_X }
            Key { keycode : Qt.Key_C }
            Key { keycode : Qt.Key_V }
            Key { keycode : Qt.Key_B }
            Key { keycode : Qt.Key_N }
            Key { keycode : Qt.Key_M }
            Key { keycode : Qt.Key_K }
            Key { keycode : Qt.Key_L }
        }
        Row {
            Key { keycode : Qt.Key_S }
        }
    }

    Keys.onPressed : {
        event.accepted = processKeyEvent( event.key, event.modifiers )
    }

    function processKeyEvent( keycode, modifiers ) {
        if ( keycode >= Qt.Key_A && keycode <= Qt.Key_Z ) {
            engine.appendCode( keycode )
        }
        return true
    }
}
