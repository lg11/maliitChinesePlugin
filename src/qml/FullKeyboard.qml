import QtQuick 1.1

Item {
    id : keyboard
    Column {
        Row {
            Key { keycode : "Q" }
            Key { keycode : "W" }
            Key { keycode : "E" }
            Key { keycode : "R" }
            Key { keycode : "T" }
            Key { keycode : "Y" }
            Key { keycode : "U" }
            Key { keycode : "I" }
            Key { keycode : "O" }
            Key { keycode : "P" }
        }
        Row {
            Key { keycode : "A" }
            Key { keycode : "S" }
            Key { keycode : "D" }
            Key { keycode : "F" }
            Key { keycode : "G" }
            Key { keycode : "H" }
            Key { keycode : "J" }
            Key { keycode : "K" }
            Key { keycode : "L" }
        }
        Row {
            Key { keycode : "Z" }
            Key { keycode : "X" }
            Key { keycode : "C" }
            Key { keycode : "V" }
            Key { keycode : "B" }
            Key { keycode : "N" }
            Key { keycode : "M" }
            Key { keycode : "K" }
            Key { keycode : "L" }
        }
        Row {
            Key { keycode : "S" }
        }
    }

    function processKeyEvent( keycode ) {
    }
}
