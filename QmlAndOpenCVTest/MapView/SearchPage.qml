import QtQuick 2.3

Rectangle
{
    color: "#0f3460"
    border.color: "#e67e22"
    border.width: 2
    // radius: 10

    Column
    {
        anchors.centerIn: parent
        spacing: 20

        Text
        {
            text: "🔍 搜索功能"
            font.pointSize: 28
            color: "#e67e22"
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // 搜索框
        Rectangle
        {
            width: 400
            height: 45
            color: "#2c3e50"
            radius: 5
            border.color: "#e67e22"
            border.width: 2

            TextInput
            {
                id: searchInput
                anchors.fill: parent
                anchors.margins: 10
                color: "white"
                font.pointSize: 14
                focus: true

                Text
                {
                    text: "请输入搜索内容..."
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#7f8c8d"
                    font.pointSize: 14
                    visible: searchInput.text.length === 0
                }
            }
        }

        Text
        {
            text: "搜索结果将显示在这里"
            font.pointSize: 14
            color: "#95a5a6"
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
