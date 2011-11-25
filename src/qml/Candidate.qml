import QtQuick 1.1

Item {
    property string selectedWord
    property string validCode
    property string invalidCode
    property string _0
    property string _1
    property string _2
    property string _3
    property string _4

    Connections {
        target : engine
        onUpdated : {
            var str = engine.getCandidateString()
            var list = str.split( "," )
            selectedWord = list[0]
            validCode = list[1]
            invalidCode = list[2]
            _0 = list[3]
            _1 = list[4]
            _2 = list[5]
            _3 = list[6]
            _4 = list[7]

            if ( selectedWord.length > 0 ) {
                if ( invalidCode.length > 0 ) 
                    inputmethod.sendPreedit( selectedWord.concat( "'", validCode ), "'".concat( invalidCode ) )
                else
                    inputmethod.sendPreedit( selectedWord.concat( "'", validCode ), invalidCode )
            }
            else {
                if ( invalidCode.length > 0 ) 
                    inputmethod.sendPreedit( validCode, "'".concat( invalidCode ) )
                else
                    inputmethod.sendPreedit( validCode, invalidCode )
            }
        }
    }
}
