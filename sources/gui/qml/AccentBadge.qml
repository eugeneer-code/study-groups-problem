import QtQuick
import QtQuick.Controls

Item {
    property alias text: label.text

    width: label.width + 8
    height: label.height

    Rectangle {
        anchors.fill: parent
        color: palette.accent
        radius: 4
        opacity: 0.2
    }
    Label {
        id: label
        anchors.centerIn: parent
        color: palette.accent
        font.bold: true
    }
}