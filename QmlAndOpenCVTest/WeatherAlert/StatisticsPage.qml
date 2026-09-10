import QtQuick 2.3

Rectangle
{
    color: "#1a1a2e"
    border.color: "#27ae60"
    border.width: 2
    // radius: 10

    Column
    {
        anchors.centerIn: parent
        spacing: 25

        Text
        {
            text: "📊 数据统计"
            font.pointSize: 28
            color: "#27ae60"
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Row
        {
            spacing: 30
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle
            {
                width: 150
                height: 100
                color: "#2c3e50"
                radius: 8

                Column
                {
                    anchors.centerIn: parent
                    spacing: 10

                    Text
                    {
                        text: "总用户数"
                        font.pointSize: 12
                        color: "#95a5a6"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Text
                    {
                        text: "1,234"
                        font.pointSize: 24
                        color: "#27ae60"
                        font.bold: true
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
            }

            Rectangle
            {
                width: 150
                height: 100
                color: "#2c3e50"
                radius: 8

                Column
                {
                    anchors.centerIn: parent
                    spacing: 10

                    Text
                    {
                        text: "今日访问"
                        font.pointSize: 12
                        color: "#95a5a6"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Text
                    {
                        text: "567"
                        font.pointSize: 24
                        color: "#3498db"
                        font.bold: true
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
            }
        }
    }
}