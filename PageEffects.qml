import QtQuick
import QtQuick.Controls 

Item {


Label {
                    x: 160
                    y: 0
                    width: 100
                    height: 20
                    color: "#ffffff"
                    wrapMode: Label.Wrap
                    font.pointSize: 14
                    font.weight: Font.Bold
                    horizontalAlignment: Qt.AlignHCenter
                    text: qsTr("Hall")
                }

 Label {
                    x: 565
                    y: 0
                    width: 100
                    height: 20
                    color: "#ffffff"
                    wrapMode: Label.Wrap
                    font.pointSize: 14
                    font.weight: Font.Bold
                    horizontalAlignment: Qt.AlignHCenter
                    text: qsTr("Chorus")
                }


  Slider {
                id: sldReverbLevel
                orientation: "Vertical"
                objectName: "sldReverbLevel"
                x: 50
                y: 44
                width: 40
                height: 267
                value: 0.5
                onValueChanged: _myClass.sliderValueChanged(value, 3)
                        MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.BlankCursor
                        enabled: false
                    }

            }

  Slider {
                id: sldReverbRoomsize
                orientation: "Vertical"
                objectName: "sldReverbRoomsize"
                x: 150
                y: 44
                width: 40
                height: 267
                value: 0.5
                onValueChanged: _myClass.sliderValueChanged(value, 4)
                MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.BlankCursor
                        enabled: false
                }
            }

  Slider {
                id: sldReverbDamp
                orientation: "Vertical"
                objectName: "sldReverbDamp"
                x: 250
                y: 44
                width: 40
                height: 267
                value: 0.5
                onValueChanged: _myClass.sliderValueChanged(value, 5)
                        MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.BlankCursor
                        enabled: false
                    }

            }

  Slider {
                id: sldReverbWidth
                orientation: "Vertical"
                objectName: "sldReverbWidth"
                x: 350
                y: 44
                width: 40
                height: 267
                value: 0.5
                onValueChanged: _myClass.sliderValueChanged(value, 6)
                        MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.BlankCursor
                        enabled: false
                    }

            }

  Slider {
                id: sldChorusLevel
                orientation: "Vertical"
                objectName: "sldChorusLevel"
                x: 500
                y: 44
                width: 40
                height: 267
                value: 0.5
                onValueChanged: _myClass.sliderValueChanged(value, 7)
                        MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.BlankCursor
                        enabled: false
                    }

            }

  Slider {
                id: sldChorusDepth
                orientation: "Vertical"
                objectName: "sldChorusDepth"
                x: 600
                y: 44
                width: 40
                height: 267
                value: 0.5
                onValueChanged: _myClass.sliderValueChanged(value, 8)
                MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.BlankCursor
                        enabled: false
                }
            }

  Slider {
                id: sldChorusSpeed
                orientation: "Vertical"
                objectName: "sldChorusSpeed"
                x: 700
                y: 44
                width: 40
                height: 267
                value: 0.5
                onValueChanged: _myClass.sliderValueChanged(value, 9)
                        MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.BlankCursor
                        enabled: false
                    }

            }

     Label {
            x: 40; y: 350;
            color: "#ffffff"; font.pointSize: 14
            text: qsTr("Stärke")
            }
     Label {
            x: 150; y: 350;
            color: "#ffffff"; font.pointSize: 14
            text: qsTr("Raum")
            }
     Label {
            x: 225; y: 350;
            color: "#ffffff"; font.pointSize: 14
            text: qsTr("Dämpfung")
            }
     Label {
            x: 350; y: 350;
            color: "#ffffff"; font.pointSize: 14
            text: qsTr("Weite")
            }

     Label {
            x: 495; y: 350;
            color: "#ffffff"; font.pointSize: 14
            text: qsTr("Stärke")
            }
     Label {
            x: 600; y: 350;
            color: "#ffffff"; font.pointSize: 14
            text: qsTr("Tiefe")
            }
     Label {
            x: 690; y: 350;
            color: "#ffffff"; font.pointSize: 14
            text: qsTr("Frequnz")
            }


}