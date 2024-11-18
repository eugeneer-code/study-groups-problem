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
                Layout.preferredHeight: 30
                Layout.preferredWidth: 130
                from: 1
                to: 100
                Component.onCompleted: value = core.peopleCount
                onValueChanged: {
                    core.peopleCount = value
                    core.gradesModel.setPeopleCount(value)
                    core.groupsModel.setPeopleCount(value)
                }
            }
            Label {text: "Количество направлений:"}
            SpinBox {
                Layout.preferredHeight: 30
                Layout.preferredWidth: 130
                from: 1
                to: core.peopleCount
                Component.onCompleted: value = core.disciplinesCount
                onValueChanged: {
                    core.disciplinesCount = value
                    core.importanceModel.setCount(value)
                    core.gradesModel.setDisciplinesCount(value)
                    core.groupsModel.setDisciplinesCount(value)
                }
            }
        }

        Row {
            spacing: 15
            Label {text: "Размер групп:"}
            AccentBadge {
                visible: core.groupsModel.freePlaces > 0
                text: "+" + core.groupsModel.freePlaces
            }
        }
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

    ColumnLayout {
        anchors {
            top: parent.top
            right: parent.right
            margins: 20
        }
        spacing: 16
        Row {
            Layout.alignment: Qt.AlignRight
            spacing: 16
            Button {
                Layout.alignment: Qt.AlignRight
                text: "Случайный набор"
                onClicked: core.regenerate()
            }
            Button {
                text: "Рассчитать"
                enabled: core.groupsModel.freePlaces == 0
                onClicked: core.solve()
            }
        }
        Label {
            Layout.alignment: Qt.AlignRight
            visible: core.totalGradesLoss >= 0
            text: "Общее отставание: <b>" + core.totalGradesLoss + "</b>"
        }
    }
}