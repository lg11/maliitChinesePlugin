import QtQuick 1.1

QtObject {
    property variant keysym 

    Component.onCompleted : {
        var buffer = Array( 128 )
        buffer[Qt.Key_0] = [ "0", "0" ]
        buffer[Qt.Key_1] = [ "1", "1" ]
        buffer[Qt.Key_2] = [ "2", "2" ]
        buffer[Qt.Key_3] = [ "3", "3" ]
        buffer[Qt.Key_4] = [ "4", "4" ]
        buffer[Qt.Key_5] = [ "5", "5" ]
        buffer[Qt.Key_6] = [ "6", "6" ]
        buffer[Qt.Key_7] = [ "7", "7" ]
        buffer[Qt.Key_8] = [ "8", "8" ]
        buffer[Qt.Key_9] = [ "9", "9" ]

        buffer[Qt.Key_A] = [ "a", "A" ]
        buffer[Qt.Key_B] = [ "b", "B" ]
        buffer[Qt.Key_C] = [ "c", "C" ]
        buffer[Qt.Key_D] = [ "d", "D" ]
        buffer[Qt.Key_E] = [ "e", "E" ]
        buffer[Qt.Key_F] = [ "f", "F" ]
        buffer[Qt.Key_G] = [ "g", "G" ]
        buffer[Qt.Key_H] = [ "h", "H" ]
        buffer[Qt.Key_I] = [ "i", "I" ]
        buffer[Qt.Key_J] = [ "j", "J" ]
        buffer[Qt.Key_K] = [ "k", "K" ]
        buffer[Qt.Key_L] = [ "l", "L" ]
        buffer[Qt.Key_M] = [ "m", "M" ]
        buffer[Qt.Key_N] = [ "n", "N" ]
        buffer[Qt.Key_O] = [ "o", "O" ]
        buffer[Qt.Key_P] = [ "p", "P" ]
        buffer[Qt.Key_Q] = [ "q", "Q" ]
        buffer[Qt.Key_R] = [ "r", "R" ]
        buffer[Qt.Key_S] = [ "s", "S" ]
        buffer[Qt.Key_T] = [ "t", "T" ]
        buffer[Qt.Key_U] = [ "u", "U" ]
        buffer[Qt.Key_V] = [ "v", "V" ]
        buffer[Qt.Key_W] = [ "w", "W" ]
        buffer[Qt.Key_X] = [ "x", "X" ]
        buffer[Qt.Key_Y] = [ "y", "Y" ]
        buffer[Qt.Key_Z] = [ "z", "Z" ]

        /*buffer[Qt.Key_Comma] = [ ",", "?", "@", "," ]*/
        /*buffer[Qt.Key_Dot] = [ ".", "!", "...", "." ]*/

        /*buffer[Qt.Key_Return] = [ "◄", "◄", "◄", "◄" ]*/
        /*buffer[Qt.Key_Space] = [ " ", "", "", " " ]*/
        /*buffer[Qt.Key_Backspace] = [ "◄", "◄", "◄", "◄" ]*/
        /*buffer[Qt.Key_Shift] = [ "▲", "▲", "▲", "▲" ]*/
        /*buffer[Qt.Key_Ctrl] = [ "", "", "", "" ]*/
        /*buffer[Qt.Key_Alt] = [ "@", "@", "@", "@" ]*/

        keysym = buffer
    }
}
