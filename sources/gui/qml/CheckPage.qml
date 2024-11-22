import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

/**
 * Страница с решением методом перебора
 */
Flickable {
    contentHeight: layout.height + 40
    contentWidth: width
    clip: true
    boundsBehavior: Flickable.StopAtBounds

    ScrollIndicator.vertical: ScrollIndicator { }

    ColumnLayout {
        id: layout
        x: 20
        y: 20
        width: parent.width - 40
        spacing: 12

        Label {
            text: "Количество вариантов: <b>  " + core.bruteforce.people + "!</b> = " + core.bruteforce.factorial
        }
        RowLayout {
            spacing: 16
            Button {
                Layout.alignment: Qt.AlignVCenter
                text: core.bruteforce.active ? "Остановить" : "Рассчитать"
                onClicked: {
                    if(core.bruteforce.active) core.stopBruteforce()
                    else core.startBruteforce()
                }
                enabled: core.groupsModel.freePlaces == 0 || core.bruteforce.active
            }
            ProgressBar {
                Layout.alignment: Qt.AlignVCenter
                width: 200
                from: 0
                to: 100
                value: core.bruteforce.progress
                visible: core.bruteforce.active
            }
            Label {
                Layout.alignment: Qt.AlignVCenter
                text: core.bruteforce.progress + "%"
                visible: core.bruteforce.active
            }
        }

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.preferredHeight: contentHeight
            model: core.bruteforce.resultModel
            delegate: Item {
                width: listView.width
                height: 30
                Rectangle {
                    anchors.fill: parent
                    color: _selected ? palette.highlight : "transparent"
                    border.width: 1
                    border.color: palette.alternateBase
                }
                Row {
                    anchors.verticalCenter: parent.verticalCenter
                    x: 6
                    Label {
                        text: "Отставание: "
                        color: palette.mid
                    }
                    Label {
                        text: _gradesLoss
                    }
                    Label {
                        text: "   Оценка: "
                        color: palette.mid
                    }
                    Label {
                        text: _cost
                    }
                    Label {
                        text: "   Решение: "
                        color: palette.mid
                    }
                    Label {
                        text: _solution
                    }
                }

            }
        }
    }
}