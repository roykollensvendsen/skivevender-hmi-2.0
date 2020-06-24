import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4
import QtQuick.Layouts 1.12
import ProgramModel 1.0

Window {
    id: window
    visible: true
    width: 480
    height: 640
    title: qsTr("skivevender-hmi-2.0")

    ProgramModel {
        id: programs
    }

    Component {
        id: highlight
        Rectangle {
            width: 180
            height: 40
            color: "lightsteelblue"
            radius: 20
            y: programListView.currentItem.y
            Behavior on y {
                SpringAnimation {
                    spring: 3
                    damping: 0.2
                }
            }
        }
    }

    Component {
        id: delegate
        Text {
            text: name
            minimumPointSize: 10
            font.pointSize: 50
            fontSizeMode: Text.Fit
            MouseArea {
                anchors.fill: parent
                onClicked: programListView.currentIndex = index
            }
        }
    }

    ListView {
        id: programListView
        anchors.fill: parent
        model: programs
        delegate: delegate
        highlight: highlight
        highlightFollowsCurrentItem: true
        focus: true
        keyNavigationEnabled: true
        interactive: true
        onCurrentItemChanged: console.log(currentIndex)
    }

    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: window.height
        width: window.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: window.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }
}
