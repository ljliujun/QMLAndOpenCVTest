import QtQuick 2.3
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

Rectangle
{
    id: titleBar
    color: "#FFFFFF"

    // 用于存储鼠标拖动时的偏移量
    property int dragOffsetX: 0
    property int dragOffsetY: 0

    // 鼠标区域用于处理窗口拖动
    MouseArea 
    {
        id: dragMouseArea
        anchors.fill: parent
        onPressed: 
        {
            dragOffsetX = mouse.x
            dragOffsetY = mouse.y
            // 使用 Windows API 实现原生拖动
            if (toolBarHandler && appWindow) 
            {
                toolBarHandler.startWindowMove(appWindow, mouse.x, mouse.y)
            }
        }
        propagateComposedEvents: false
    }

    Rectangle 
    {
        width: parent.width
        height: 1
        color: "#E0E0E0"
        anchors.bottom: parent.bottom
    }

    RowLayout 
    {
        id: rowLayout
        anchors.fill: parent
        anchors.bottomMargin: 1
        spacing: 0

        Text 
        {
            text: "天气助手"
            font.pixelSize: 20
            Layout.leftMargin: 10
        }
        Item { Layout.fillWidth: true }
        // ========== 中间内容区 ==========
        Rectangle 
        {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"

            Rectangle 
            {
                id: searchBox
                width: parent.width
                height: parent.height * 2 / 3
                radius: 22
                color: "#FFFFFF"
                border.color: "#D0D0D0"
                border.width: 1
                anchors.centerIn: parent

                RowLayout 
                {
                    anchors.fill: parent
                    anchors.leftMargin: 16
                    anchors.rightMargin: 8
                    // 上下边距对称，或者直接用 verticalCenter 居中
                    anchors.topMargin: 4
                    anchors.bottomMargin: 8
                    spacing: 0

                    TextField 
                    {
                        id: searchInput
                        Layout.fillWidth: true
                        Layout.preferredHeight: 20        // 固定高度，不要 fillHeight
                        Layout.alignment: Qt.AlignVCenter  // 垂直居中
                        placeholderText: "请输入城市名称搜索天气..."
                        font.pixelSize: 14
                        verticalAlignment: TextInput.AlignVCenter
                        // 关键：去掉默认内边距，让文字有更多显示空间
                        topPadding: 0
                        bottomPadding: 0
                        leftPadding: 0
                        rightPadding: 0
                        
                        background: Rectangle {
                            color: "transparent"
                            border.width: 0
                        }
                    }

                    Button 
                    {
                        id: searchButton
                        text: "搜索"
                        flat: true
                        Layout.preferredWidth: 50
                        Layout.preferredHeight: 20
                        Layout.alignment: Qt.AlignVCenter  // 垂直居中
                        font.pixelSize: 13
                        onClicked: {
                            console.log("搜索城市:", searchInput.text)
                        }
                    }
                }
            }
        }
        Item { Layout.fillWidth: true }
        Button 
        {
            id: model
            text: "夜间模式"
            flat: true                          // 背景透明
            Layout.preferredWidth: 70
            Layout.preferredHeight: 30
            font.pixelSize: 11
        }
        Button 
        {
            id: settings
            text: "设置"
            flat: true                          // 背景透明
            Layout.preferredWidth: 50
            Layout.preferredHeight: 30
            font.pixelSize: 11
        }
        Button 
        {
            id: about
            text: "关于"
            flat: true                          // 背景透明
            Layout.preferredWidth: 50
            Layout.preferredHeight: 30
            font.pixelSize: 11
        }
        Button 
        {
            id: minimizeButton
            flat: true
            Layout.preferredWidth: 36
            Layout.preferredHeight: 30
            
            // 确保按钮可以接收鼠标事件
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    appWindow.visibility = Window.Minimized
                }
            }
            
            Image 
            {
                anchors.centerIn: parent
                source: "qrc:/Icon/Icon/min.svg"
                width: 16
                height: 16

                onStatusChanged: {
                    if (status === Image.Error) {
                        console.error("Failed to load SVG:", source)
                    } else if (status === Image.Ready) {
                        console.log("SVG loaded successfully:", source)
                    }
                }
            }
        }

        Button 
        {
            id: maximizeButton
            flat: true
            Layout.preferredWidth: 36
            Layout.preferredHeight: 30
            
            // 根据窗口状态动态切换图标
            property bool isMaximized: appWindow.visibility === Window.Maximized
            
            onClicked: 
            {
                if (appWindow.visibility === Window.Maximized)
                {
                    appWindow.visibility = Window.Windowed
                } else 
                {
                    appWindow.visibility = Window.Maximized
                }
            }
            
            Image 
            {
                anchors.centerIn: parent
                source: maximizeButton.isMaximized ? "qrc:/Icon/Icon/minScreen.svg" : "qrc:/Icon/Icon/fullScreen.svg"
                width: 16
                height: 16
            }
        }

        Button 
        {
            id: closeButton
            flat: true
            Layout.preferredWidth: 36
            Layout.preferredHeight: 30
            
            MouseArea {
                anchors.fill: parent
                onClicked: Qt.quit()
            }
            
            Image 
            {
                anchors.centerIn: parent
                source: "qrc:/Icon/Icon/close.svg"
                width: 16
                height: 16
            }
        }
    }
}