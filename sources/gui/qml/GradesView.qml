import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.qmlmodels

TableView {
    model: core.gradesModel
    boundsBehavior: Flickable.StopAtBounds
    delegate: Rectangle {
        implicitWidth: 70
        implicitHeight: 30
        border.width: 1
        border.color: palette.alternateBase
        color: _selected ? palette.highlight : "transparent"

        Text {
            anchors.centerIn: parent
            text: _grade
        }

        TableView.editDelegate: TextField {
            anchors.fill: parent
            text: _grade
            horizontalAlignment: TextInput.AlignHCenter
            verticalAlignment: TextInput.AlignVCenter
            Component.onCompleted: selectAll()

            TableView.onCommit: {
                _grade = text
            }
        }
    }
}