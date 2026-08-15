import QtQuick 2.15
import QtQuick.Controls 2.15

MenuItem
{
    id: menuItem

    height: 32

    contentItem: Text {
        text: menuItem.action ? menuItem.action.text : ""
        font.pixelSize: 14
        color: menuItem.highlighted ? "#ffffff" : "#000000"
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 12
        elide: Text.ElideRight
    }

    background: Rectangle {
        anchors.fill: parent
        color: menuItem.highlighted ? "#0658c6" : "transparent"
    }
}