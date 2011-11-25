import QtQuick 1.1

Item {
    Candidate { id : candidate }

    Item {
        id : mark
        anchors.horizontalCenter : parent.left
        width : 40
        height : 10
        clip : true
        Rectangle {
            anchors.centerIn : parent
            anchors.verticalCenterOffset : 10
            width : 20
            height : 20
            color : "gray"
            rotation : 45
        }
    }
    Column {
        y : mark.y + mark.height
        x : mark.x
        spacing : 1
        /*Rectangle {*/
            /*color : "gray"*/
            /*height : 60*/
            /*width : 300*/
            /*Flow {*/
                /*spacing : 4*/
                /*Text { text : candidate.selectedWord ; color : "white" ; textFormat : Text.PlainText ; font.pixelSize : 26 }*/
                /*Text { text : candidate.validCode ; color : "white" ; textFormat : Text.PlainText ; font.pixelSize : 26 }*/
                /*Text { text : candidate.invalidCode ; color : "red" ; textFormat : Text.PlainText ; font.pixelSize : 26 }*/
            /*}*/
        /*}*/
        Row {
            spacing : 1
            CandidateItem{ text : candidate._0 }
            CandidateItem{ text : candidate._1 }
            CandidateItem{ text : candidate._2 }
            CandidateItem{ text : candidate._3 }
            CandidateItem{ text : candidate._4 }
        }
    }

    Connections {
        target : inputmethod
        onCursorRectChanged : {
            x = cursorRect.x
            y = cursorRect.y + cursorRect.height
        }
    }
}
