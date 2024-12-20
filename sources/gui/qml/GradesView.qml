import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.qmlmodels

/**
 * Отображение и редактирование оценок
 */
TableView {
    model: core.gradesModel
    boundsBehavior: Flickable.StopAtBounds
    clip: true
    delegate: Rectangle {
        implicitWidth: 50
        implicitHeight: 30
        border.width: 1
        border.color: _selected ? palette.highlight : "#ddd"
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

            validator: IntValidator{
                bottom: 1
                top: 5
            }

            TableView.onCommit: {
                _grade = text
            }
        }
    }
}