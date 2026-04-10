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
            text: qsTr("Styles:")
        }

        Rectangle {
            x: 0
            y: 40
            width: 400
            height: 380
            color: "black"

            Component {
                id: styleDelegate
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
                id: lvSequencerStyles
                objectName: "lvSequencerStyles"
                anchors.fill: parent
                delegate: styleDelegate
                focus: true
                clip: true

                /*
                onCurrentIndexChanged: {
                    if (currentIndex !== -1) {
                        //_myClass.soundFontChanged(currentItem.text);
                    }
                }
                */
            }

            Button {
                id: btnSequencerLoadStyles
                objectName: "btnSequencerLoadStyles"
                x: 10
                y: 400
                // width: 100
                // height: 44
                text: qsTr("Styles Laden")
                font.pointSize: 14
                font.weight: Font.Bold
                onClicked:{
                    _myClass.sequencerCmdLoadStyles();
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



            Button {
                id: btnSequencerLoadStyle
                objectName: "btnSequencerLoadStyle"
                x: 152
                y: 400
                // width: 100
                // height: 44
                text: qsTr("Style Laden")
                font.pointSize: 14
                font.weight: Font.Bold
                onClicked:{
                    //_myClass.sequencerCmdLoadStyles();
                    _myClass.sequencerCmdLoadStyle(lvSequencerStyles.currentIndex);
                    txtSequencerCurrentStyle.text = lvSequencerStyles.currentItem.text;
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
            id: txtSequencerCurrentStyle
            objectName: "txtSequencerCurrentStyle"
            width: 100
            height: 40
            font.pointSize: 14
            font.weight: Font.Bold
            color: "#ffffff"
            text: qsTr("Kein Style geladen.")
        }

        Button {
                id: btnSequencerStart
                objectName: "btnSequencerStart"
                x: 40
                y: 80
                // width: 100
                // height: 44
                text: qsTr("Start")
                font.pointSize: 14
                font.weight: Font.Bold
                enabled: true;
                onClicked:{
                    _myClass.sequencerCmdStart();    
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
                id: btnSequencerStop
                objectName: "btnSequencerStop"
                x: 140
                y: 80
                // width: 100
                // height: 44
                enabled: true;
                text: qsTr("Stop")
                font.pointSize: 14
                font.weight: Font.Bold
                onClicked:{
                    _myClass.sequencerCmdStop();
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
            id: txtSequencerTime
            objectName: "txtSequencerTime"
            width: 100
            height: 40
            font.pointSize: 14
            font.weight: Font.Bold
            color: "#ffffff"
            text: qsTr("00/00")
        }

 Slider {
                id: sldSequencerTempo
                orientation: "Horizontal"
                objectName: "sldSequencerTempo"
                x: 20
                y: 120
                width: 267
                height: 40
                value: 0.33333
                onValueChanged: _myClass.sequencerCmdSetTempo(value)
                        MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.BlankCursor
                        enabled: false
                    }

            }


        BusyIndicator {
            id: biSequencerbusy
            objectName: "biSequencerbusy"

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