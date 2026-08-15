import QtQuick 2.3

Rectangle
{
    color: "#16213e"
    border.color: "#e74c3c"
    border.width: 2
    // radius: 10

    Column
    {
        anchors.centerIn: parent
        spacing: 20

        Text
        {
            text: "❓ 帮助文档"
            font.pointSize: 28
            color: "#e74c3c"
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text
        {
            text: "常见问题与使用指南"
            font.pointSize: 16
            color: "#ecf0f1"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // 帮助列表
        ListView
        {
            width: 400
            height: 200
            spacing: 20
            model: ListModel
            {
                ListElement { title: "如何开始使用？" }
                ListElement { title: "系统配置说明" }
                ListElement { title: "常见问题解答" }
                ListElement { title: "联系技术支持" }
            }

            delegate: Rectangle
            {
                width: parent.width
                height: 45
                color: mouseArea.containsMouse ? "#34495e" : "#2c3e50"
                radius: 5

                Text
                {
                    text: title
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    font.pointSize: 14
                    color: "white"
                }

                MouseArea
                {
                    id: mouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: console.log("点击了: " + title)
                }
            }
        }
    }
}