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
            text: qsTr("Soundfonts:")
        }

        Rectangle {
            x: 0
            y: 40
            width: 400
            height: 380
            color: "black"

            Component {
                id: nameDelegate

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
                objectName: "lvSoundFonts"
                anchors.fill: parent
                delegate: nameDelegate
                focus: true
                clip: true

                onCurrentIndexChanged: {
                    if (currentIndex !== -1) {
                        _myClass.soundFontChanged(currentItem.text);
                    }
                }
            }

            Button {
                id: btnLoadSoundFont
                objectName: "btnLoadSoundFont"
                x: 152
                y: 400
                // width: 100
                // height: 44
                text: qsTr("Soundfont Laden")
                font.pointSize: 14
                font.weight: Font.Bold
                onClicked:{
                    _myClass.loadSoundFont();
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
            id: txtCurrentSoundFont
            objectName: "txtCurrentSoundFont"
            width: 100
            height: 40
            font.pointSize: 14
            font.weight: Font.Bold
            color: "#ffffff"
            text: qsTr("Soundfont geladen.")
        }


        BusyIndicator {
            id: busyIndicator
            objectName: "busyIndicator"

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
            //Material.accent: "red"
        }
    }
}