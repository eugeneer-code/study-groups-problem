import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

/**
 * Отображение и редактирование размера учебных групп
 */
TableView {
    model: core.groupsModel
    boundsBehavior: Flickable.StopAtBounds
    clip: true
    delegate: Rectangle {
        implicitWidth: 50
        implicitHeight: 30
        border.width: 1
        border.color: palette.alternateBase

        Text {
            anchors.centerIn: parent
            text: _groupSize
        }

        TableView.editDelegate: SpinBox {
            anchors.centerIn: parent
            width: 130
            height: 30
            value: _groupSize
            editable: true
            from: 1
            to: _maxSize

            TableView.onCommit: {
                _groupSize = value
            }
        }
    }
}