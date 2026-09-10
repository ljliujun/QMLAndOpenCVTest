import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

WeatherCard {
    id: hourlyForecasrCard

  // 根据 OpenWeatherMap 的 icon code 返回 emoji
    // icon code 格式：XXd（白天）或 XXn（夜晚），XX 取值 01/02/03/04/09/10/11/13/50
    function weatherEmoji(code) {
        if (!code) return "☁️"
        var prefix = code.substring(0, 2)
        var isDay = code.indexOf("d") >= 0
        if (prefix === "01") return isDay ? "☀️" : "🌙"   // 晴
        if (prefix === "02") return isDay ? "⛅" : "☁️"   // 少云
        if (prefix === "03") return "☁️"                    // 多云
        if (prefix === "04") return "☁️"                    // 阴
        if (prefix === "09") return "🌧️"                    // 阵雨
        if (prefix === "10") return "🌧️"                    // 雨
        if (prefix === "11") return "⛈️"                    // 雷暴
        if (prefix === "13") return "❄️"                    // 雪
        if (prefix === "50") return "🌫️"                    // 雾
        return "☁️"
    }

    // 顶部标题栏
    Row 
    {
        id: headerRow
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 10
        anchors.leftMargin: 20
        height: 24

        Text {
            text: "未来5天天气预报"
            font.pointSize: 9
            font.bold: true
            color: "#333333"
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            text: ">"
            font.pointSize: 9
            color: "#999999"
            anchors.left: parent.left
            anchors.leftMargin: 100
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    // 外层布局：精准锚定在标题栏下方
    ColumnLayout 
    {
        anchors.top: headerRow.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottomMargin: 10
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 10
        spacing: 0

        // 横向天气预报列表
        ListView 
        {
            id: listView
           
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true  // 开启裁剪，防止子项超出边界显示

            orientation: ListView.Horizontal
            layoutDirection: Qt.LeftToRight
            spacing: 4

            model: weatherManager ? weatherManager.forecastModel : null

            delegate: Item
            {
                id: delegateItem
                width: 60
                height: listView.height

                ColumnLayout
                {
                    anchors.fill: parent
                    anchors.bottomMargin: 15
                    spacing: 2

                    Text {
                        text: model.time
                        font.pointSize: 9
                        color: "#666666"
                        font.bold: (index === 0)
                        Layout.alignment: Qt.AlignHCenter
                        Layout.preferredWidth: delegateItem.width
                        horizontalAlignment: Text.AlignHCenter
                        clip: true
                        elide: Text.ElideRight
                    }

                    Item { Layout.fillHeight: true }

                    Text {
                        text: weatherEmoji(model.icon)
                        font.pointSize: 18
                        Layout.alignment: Qt.AlignHCenter
                    }

                    Item { Layout.fillHeight: true }

                    Text {
                        text: Math.round(model.temp) + "℃"
                        font.pointSize: 12
                        font.bold: true
                        color: "#222222"
                        Layout.alignment: Qt.AlignHCenter
                    }

                    Text {
                        text: model.description
                        font.pointSize: 8
                        color: "#999999"
                        Layout.alignment: Qt.AlignHCenter
                        Layout.preferredWidth: delegateItem.width
                        horizontalAlignment: Text.AlignHCenter
                        clip: true
                        elide: Text.ElideRight
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: console.log("选中:", model.time)
                }
            }

            // 添加水平滚动条
            ScrollBar.horizontal: ScrollBar 
            {
                policy: ScrollBar.AsNeeded
                contentItem: Rectangle
                {
                    implicitHeight: 4
                    radius: 2
                    color: "#546bff"
                }
                // background: Rectangle 
                // {
                //     implicitHeight: 4
                //     radius: 2
                //     // color: "#DDDDDD"
                // }
            }
        }
    }
}