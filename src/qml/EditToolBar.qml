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
            color : engine.active ? "cornflowerblue" : "gray"
            /*color : "gray"*/
            rotation : 45
        }
    }
    Row {
        y : mark.y + mark.height + 1
        x : mark.x 
        spacing : 1
        CandidateItem{ text : candidate._0 }
        CandidateItem{ text : candidate._1 }
        CandidateItem{ text : candidate._2 }
        CandidateItem{ text : candidate._3 }
        CandidateItem{ text : candidate._4 }
    }

    Connections {
        target : inputmethod
        onCursorRectChanged : {
            var pos = root.mapToItem( canvas, cursorRect.x, cursorRect.y )
            x = pos.x
            y = pos.y + cursorRect.height + 1
        }
    }
}
