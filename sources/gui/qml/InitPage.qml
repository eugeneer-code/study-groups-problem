import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.qmlmodels

Item {

    ColumnLayout {
        anchors {
            fill: parent
            margins: 20
        }

        GridLayout {
            columns: 2
            columnSpacing: 20
            Label {text: "Количество претендентов:"}
            SpinBox {
                from: 1
                to: 100
                onValueChanged: {
                    core.gradesModel.setPeopleCount(value)
                    core.groupsModel.setPeopleCount(value)
                }
            }
            Label {text: "Количество направлений:"}
            SpinBox {
                from: 1
                to: 100
                onValueChanged: {
                    core.importanceModel.setCount(value)
                    core.gradesModel.setDisciplinesCount(value)
                    core.groupsModel.setDisciplinesCount(value)
                }
            }
        }

        Label {text: "Размер групп:"}
        GroupsView {
            Layout.preferredHeight: 30
            Layout.fillWidth: true
        }

        Label {text: "Важность направлений:"}
        ImportanceView {
            Layout.preferredHeight: 30
            Layout.fillWidth: true
        }

        Label {text: "Оценки:"}
        GradesView {
            Layout.fillWidth: true
            Layout.preferredHeight: contentHeight
        }

        Item {
            Layout.fillHeight: true
        }
    }
}