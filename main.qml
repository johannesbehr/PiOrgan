import QtQuick
import QtQuick.Controls

Window {
    visible: true
    title: qsTr("PI Organ")
    color: "black"
    visibility: Window.FullScreen
    
    property real defaultWidth: 800
    property real defaultHeight: 480

    MouseArea {
        anchors.fill: parent
        enabled: false
        cursorShape: Qt.BlankCursor
    }

    SwipeView{

        id: view
        anchors.fill: parent
        currentIndex: 0

        // Scale Window to fullscreen
        transform: Scale { 
            xScale: screenWidth / defaultWidth
            yScale: screenHeight / defaultHeight
        }

        PageInstruments {
            id: item1
        }
                   
        PageEffects {
            id: item2
        }

        PageLoadSoundFont {
            id: item3
        }

        PageMidiPlayer {
            id: item4
        }

    }

}