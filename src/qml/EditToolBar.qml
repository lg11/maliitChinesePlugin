import QtQuick 1.1

Rectangle {
    Candidate { id : candidate }

    Row {
        CandidateItem{ text : candidate._0 }
        CandidateItem{ text : candidate._1 }
        CandidateItem{ text : candidate._2 }
        CandidateItem{ text : candidate._3 }
        CandidateItem{ text : candidate._4 }
    }

    Connections {
        target : inputmethod
        onCursorRectChanged : {
        }
    }
}
