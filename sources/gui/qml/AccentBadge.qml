import QtQuick
import QtQuick.Controls

/**
 * Цветная панель с заданным текстом
 * Используется для отображения количества свободных мест
 */
Item {
    property alias text: label.text

    width: label.width + 8
    height: label.height

    Rectangle {
        anchors.fill: parent
        color: "#008F75"
        radius: 4
        opacity: 0.2
    }
    Label {
        id: label
        anchors.centerIn: parent
        color: "#008F75"
        font.bold: true
    }
}