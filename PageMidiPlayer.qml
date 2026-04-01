import QtQuick
import QtQuick.Controls 

Item {
    Rectangle {
        color: "black"
        anchors.fill: parent

        Label {
            x: 0
            y: 0
            font.pointSize: 14
            font.weight: Font.Bold
            color: "#ffffff"
            text: qsTr("Midi-Dateien:")
        }

        Rectangle {
            x: 0
            y: 40
            width: 400
            height: 380
            color: "black"

            Component {
                id: nameDelegate2
                Text {
                    readonly property ListView __lv: ListView.view
                    width: parent ? parent.width :0;
                    text: modelData;
                    font.pixelSize: 20
                    color: ListView.isCurrentItem ? "#7Fff7F" : "gray"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: __lv.currentIndex = model.index
                    }
                }
            }

            ListView {
                id: lvMidiFiles
                objectName: "lvMidiFiles"
                anchors.fill: parent
                delegate: nameDelegate2
                focus: true
                clip: true

                onCurrentIndexChanged: {
                    if (currentIndex !== -1) {
                        //_myClass.soundFontChanged(currentItem.text);
                    }
                }
            }

            Button {
                id: btnLoadMidiFile
                objectName: "btnLoadMidiFile"
                x: 152
                y: 400
                // width: 100
                // height: 44
                text: qsTr("Datei Laden")
                font.pointSize: 14
                font.weight: Font.Bold
                onClicked:{
                    _myClass.loadMidiFile(lvMidiFiles.currentItem.text);
                    txtCurrentMidiFile.text = lvMidiFiles.currentItem.text;
                }

                palette {
                    button: "#303030"
                    buttonText: "white"
                }
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.BlankCursor
                    enabled: false
                }

            }

        }
    }

    Rectangle {
        x: 400
        y:0
        width: 400
        height: parent.height
        color: "black"

        Label {
            x: 20
            y: 20
            id: txtCurrentMidiFile
            objectName: "txtCurrentMidiFile"
            width: 100
            height: 40
            font.pointSize: 14
            font.weight: Font.Bold
            color: "#ffffff"
            text: qsTr("Keine Midi-Datei geladen.")
        }

        Button {
                id: btnPlayMidiFile
                objectName: "btnPlayMidiFile"
                x: 40
                y: 80
                // width: 100
                // height: 44
                text: qsTr("Play")
                font.pointSize: 14
                font.weight: Font.Bold
                enabled: false;
                onClicked:{
                    _myClass.playMidiFile();    
                }

                palette {
                    button: "#303030"
                    buttonText: "gray"
                }
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.BlankCursor
                    enabled: false
                }
            }

        Button {
                id: btnStopMidiFile
                objectName: "btnStopMidiFile"
                x: 140
                y: 80
                // width: 100
                // height: 44
                enabled: false;
                text: qsTr("Stop")
                font.pointSize: 14
                font.weight: Font.Bold
                onClicked:{
                    _myClass.stopMidiFile();
                }

                palette {
                    button: "#303030"
                    buttonText: "gray"
                }
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.BlankCursor
                    enabled: false
                }
            }


        Label {
            x: 240
            y: 80
            id: txtMidiTime
            objectName: "txtMidiTime"
            width: 100
            height: 40
            font.pointSize: 14
            font.weight: Font.Bold
            color: "#ffffff"
            text: qsTr("0:00:00")
        }

 Slider {
                id: sldMidiSpeed
                orientation: "Horizontal"
                objectName: "sldMidiSpeed"
                x: 20
                y: 120
                width: 267
                height: 40
                value: 0.33333
                onValueChanged: _myClass.midiSpeedValueChanged(value)
                        MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.BlankCursor
                        enabled: false
                    }

            }


        BusyIndicator {
            id: busyIndicator2
            objectName: "busyIndicator2"

            x: 50
            y: 50
            width: 80
            height: 80
            palette {
                dark: "red"
                text: "green"
            }
            visible: true
            running: false
        }
    }
}