import QtQuick
import QtQuick.Controls

TabButton {
    id: btn
    implicitWidth: _title.implicitWidth + 24
    implicitHeight: 32
    background: Rectangle {
        anchors.fill: parent
        color: btn.checked ? "#FFF" : "#ebecec"
        Rectangle {
            anchors {
                right: parent.right
                verticalCenter: parent.verticalCenter
            }
            width: 1
            height: 20
            color: "#DEDFE0"
            visible: !btn.checked
        }
    }
    contentItem: Item {
        id: _contentItem
        Label {
            anchors.centerIn: parent
            id: _title
            text: btn.text
            font.bold: true
            font.pixelSize: 13
            color: btn.checked ? "#393C3E" : "#7F8283"
        }
    }
}