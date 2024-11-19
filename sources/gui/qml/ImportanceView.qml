import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

TableView {
    model: core.importanceModel
    boundsBehavior: Flickable.StopAtBounds
    clip: true
    delegate: Rectangle {
        implicitWidth: 50
        implicitHeight: 30
        border.width: 1
        border.color: palette.alternateBase

        Text {
            anchors.centerIn: parent
            text: display
        }

        TableView.editDelegate: TextField {
            anchors.fill: parent
            text: display
            horizontalAlignment: TextInput.AlignHCenter
            verticalAlignment: TextInput.AlignVCenter
            Component.onCompleted: selectAll()

            TableView.onCommit: {
                display = text
            }
        }
    }
}