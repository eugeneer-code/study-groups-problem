import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCore

/**
 * Страница с поиском решения методом ветвей и границ
 */
Flickable {
    contentHeight: layout.height + 40
    contentWidth: width
    clip: true
    boundsBehavior: Flickable.StopAtBounds

    ScrollIndicator.vertical: ScrollIndicator { }

    Settings {
        id: settings
        property var peopleCount: 1
        property var disciplinesCount: 1
    }

    Component.onCompleted: {
        peopleSpinbox.value = settings.peopleCount
        disciplinesSpinBox.value = settings.disciplinesCount
    }

    ColumnLayout {
        id: layout
        x: 20
        y: 20
        width: parent.width - 40

        GridLayout {
            columns: 2
            columnSpacing: 20
            Label {text: "Количество претендентов:"}
            SpinBox {
                id: peopleSpinbox
                Layout.preferredHeight: 30
                Layout.preferredWidth: 130
                from: 1
                to: 100
                Component.onCompleted: value = core.peopleCount
                onValueChanged: {
                    core.peopleCount = value
                    core.gradesModel.setPeopleCount(value)
                    core.groupsModel.setPeopleCount(value)
                    settings.peopleCount = value
                }
            }
            Label {text: "Количество направлений:"}
            SpinBox {
                id: disciplinesSpinBox
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
                    settings.disciplinesCount = value
                }
            }
        }

        Row {
            Layout.topMargin: 15
            spacing: 15
            Label {
                text: "Размер групп:"
            }
            AccentBadge {
                visible: core.groupsModel.freePlaces > 0
                text: "+" + core.groupsModel.freePlaces
            }
        }
        GroupsView {
            id: groupsTable
            Layout.preferredHeight: 30
            Layout.fillWidth: true
            Layout.leftMargin: -20
            Layout.rightMargin: -20
            leftMargin: 20
            rightMargin: 20
        }

        Label {
            Layout.topMargin: 15
            text: "Важность направлений:"
        }
        ImportanceView {
            id: importanceTable
            Layout.preferredHeight: 30
            Layout.fillWidth: true
            Layout.leftMargin: -20
            Layout.rightMargin: -20
            leftMargin: 20
            rightMargin: 20
            syncView: groupsTable
        }

        Label {
            Layout.topMargin: 15
            text: "Оценки:"
        }
        GradesView {
            Layout.fillWidth: true
            Layout.leftMargin: -20
            Layout.rightMargin: -20
            leftMargin: 20
            rightMargin: 20
            Layout.preferredHeight: contentHeight
            syncView: groupsTable
            syncDirection: Qt.Horizontal
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
            BusyIndicator {
                visible: core.solving
                height: 40
                width: 40
            }
            Button {
                Layout.alignment: Qt.AlignRight
                text: "Случайный набор"
                onClicked: core.regenerate()
            }
            Button {
                text: "Рассчитать"
                enabled: core.groupsModel.freePlaces == 0 && !core.solving
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