import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

WeatherCard {
    id: hourlyForecasrCard
    // 给个明确的尺寸便于调试

    ListModel 
    {
        id: tempModel
        ListElement { time: "现在"; icon: ""; temp: "28°C" }
        ListElement { time: "11:00"; icon: ""; temp: "30°C" }
        ListElement { time: "14:00"; icon: ""; temp: "32°C" }
        ListElement { time: "17:00"; icon: ""; temp: "31°C" }
        ListElement { time: "20:00"; icon: ""; temp: "29°C" }
        ListElement { time: "23:00"; icon: ""; temp: "27°C" }
        ListElement { time: "23:00"; icon: ""; temp: "27°C" }
        ListElement { time: "23:00"; icon: ""; temp: "27°C" }
        ListElement { time: "23:00"; icon: ""; temp: "27°C" }
        ListElement { time: "23:00"; icon: ""; temp: "27°C" }
        ListElement { time: "23:00"; icon: ""; temp: "27°C" }
        ListElement { time: "23:00"; icon: ""; temp: "27°C" }
        ListElement { time: "23:00"; icon: ""; temp: "27°C" }
        ListElement { time: "23:00"; icon: ""; temp: "27°C" }
        ListElement { time: "23:00"; icon: ""; temp: "27°C" }
        ListElement { time: "23:00"; icon: ""; temp: "27°C" }
        ListElement { time: "23:00"; icon: ""; temp: "27°C" }
        ListElement { time: "23:00"; icon: ""; temp: "27°C" }
        ListElement { time: "23:00"; icon: ""; temp: "27°C" }
        ListElement { time: "23:00"; icon: ""; temp: "27°C" }
        ListElement { time: "23:00"; icon: ""; temp: "27°C" }
        ListElement { time: "23:00"; icon: ""; temp: "27°C" }
        ListElement { time: "23:00"; icon: ""; temp: "27°C" }
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
            text: "24小时天气预报"
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
            // 🔥 修复：在 Layout 里面不要用 anchors.fill，改用 Layout 属性
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true  // 🔥 核心修复：开启裁剪，防止子项超出边界显示

            orientation: ListView.Horizontal
            layoutDirection: Qt.LeftToRight
            spacing: 4

            model: tempModel

            delegate: Item
            {
                id: delegateItem
                width: 45
                height: listView.height

                // 🔥 修复：内部也改用 ColumnLayout
                ColumnLayout 
                {
                    // 🔥 关键：去掉 anchors.centerIn，改为填充整个父容器
                    anchors.fill: parent
                    // spacing: 16 (注释掉，因为现在已经由两个 Item 动态分配间距了)
                    anchors.bottomMargin: 15   // 🔥 增加底部边距，避开水平滚动条

                    Text 
                    {
                        text: model.time
                        font.pointSize: 12
                        color: (index === 0) ? "#333333" : "#666666"
                        font.bold: (index === 0)
                        Layout.alignment: Qt.AlignHCenter
                    }

                    // 🔥 弹性占位符 1（会在 Time 和 Icon 之间自动分配垂直空间）
                    Item 
                    {
                        Layout.fillHeight: true
                    }

                    Image 
                    {
                        source: model.icon || "qrc:/Icon/Icon/fullScreen.svg"
                        Layout.preferredWidth: 28
                        Layout.preferredHeight: 28
                        fillMode: Image.PreserveAspectFit
                        Layout.alignment: Qt.AlignHCenter
                    }

                    // 🔥 弹性占位符 2（会在 Icon 和 Temp 之间自动分配垂直空间）
                    Item 
                    {
                        Layout.fillHeight: true
                    }

                    Text 
                    {
                        text: model.temp
                        font.pointSize: 12
                        font.bold: true
                        color: "#222222"
                        Layout.alignment: Qt.AlignHCenter
                    }
                }

                // // 蓝色选中指示条
                // Rectangle
                // {
                //     width: 20
                //     height: 3
                //     radius: 2
                //     color: "#1A73E8"
                //     anchors.bottom: parent.bottom
                //     anchors.bottomMargin: 2
                //     anchors.horizontalCenter: parent.horizontalCenter
                //     visible: index === 0
                // }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("选中:", model.time)
                    }
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