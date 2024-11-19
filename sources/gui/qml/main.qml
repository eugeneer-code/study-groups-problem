import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCore

ApplicationWindow {
    id: window
    width: 800
    height: 600
    minimumWidth: 650
    visible: true
    title: "Распределение по направлениям"

    Settings {
        property alias x: window.x
        property alias y: window.y
        property alias width: window.width
        property alias height: window.height
    }

    Component.onCompleted: {
        palette.accent = "#008F75"
        palette.highlight = "#C9EAE3"
    }

    TabBar {
        id: tabs
        width: parent.width
        StyledTabButton {
            text: "Начальные условия"
            width: implicitWidth
        }
        StyledTabButton {
            id: btn
            text: "Проверка перебором"
            width: implicitWidth
        }
        background: Rectangle {
            anchors.fill: parent
            color: "#ebecec"
        }
    }

    StackLayout {
        anchors.bottom: parent.bottom
        width: parent.width
        height: parent.height - tabs.height - 1
        currentIndex: tabs.currentIndex
        InitPage {}
        CheckPage {}
    }

}