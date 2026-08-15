import QtQuick 2.3

Rectangle
{
    color: "#16213e"
    border.color: "#9b59b6"
    border.width: 2
    // radius: 10

    Column
    {
        anchors.centerIn: parent
        spacing: 20

        Text
        {
            text: "⚙️ 系统设置"
            font.pointSize: 28
            color: "#9b59b6"
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text
        {
            text: "在这里配置系统参数和选项"
            font.pointSize: 16
            color: "#ecf0f1"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // 模拟设置项
        Rectangle
        {
            width: 300
            height: 40
            color: "#2c3e50"
            radius: 5

            Text
            {
                text: "语言: 中文"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 15
                font.pointSize: 14
                color: "white"
            }
        }

        Rectangle
        {
            width: 300
            height: 40
            color: "#2c3e50"
            radius: 5

            Text
            {
                text: "主题: 深色模式"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 15
                font.pointSize: 14
                color: "white"
            }
        }
    }
}