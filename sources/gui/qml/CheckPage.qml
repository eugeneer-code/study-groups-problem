import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

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
            text: "Количество вариантов: <b>  " + core.bruteforce.disciplines + "!</b> = " + core.bruteforce.factorial
        }
        RowLayout {
            spacing: 16
            Button {
                Layout.alignment: Qt.AlignVCenter
                text: "Рассчитать"
                onClicked: core.bruteforce.start()
            }
            ProgressBar {
                Layout.alignment: Qt.AlignVCenter
                width: 200
                from: 0
                to: 100
                value: 10
            }
            Label {
                Layout.alignment: Qt.AlignVCenter
                text: "10%"
            }
        }
    }
}