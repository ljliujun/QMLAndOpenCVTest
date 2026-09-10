import QtQuick 2.3
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.15

Button
{
    property string btnIcon: ""
    property color btnColor: "#FFFFFF"
    // property color btnBorder: "#2980b9"

    width: parent.width
    height: 50
    font.pixelSize: 12

    background: Rectangle
    {
        color: parent.hovered ? "#253ebc" : btnColor
        // radius: 0
        // border.color: btnBorder
        // border.width: 1
    }

    contentItem: RowLayout
    {
        // anchors.fill: parent
        // anchors.leftMargin: 16
        // anchors.rightMargin: 16
        // spacing: 10

        Text
        {
            text: btnIcon
            font.pixelSize: 15
            Layout.alignment: Qt.AlignVCenter
        }

        Text
        {
            text: parent.parent.text      // 读取 Button.text
            font: parent.parent.font
            color: "black"
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
        }

    }
}