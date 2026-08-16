import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

ApplicationWindow 
{
    id: appWindow
    visible: true
    width: 1200
    height: 800
    title: "Hello World"
    
    
    // 去除系统标题栏，实现无边框窗口
    flags: Qt.FramelessWindowHint | Qt.Window
    
    ColumnLayout
    {
        anchors.fill: parent
        spacing: 0
        
        TopWidget
        {
            Layout.fillWidth: true
            Layout.preferredHeight: 40
        }
        Rectangle 
        {
            Layout.fillWidth: true
            Layout.fillHeight: true
            RowLayout
            {
                anchors.fill: parent
                
                // 左侧工具栏
                Rectangle
                {
                    id: toolBar
                    Layout.preferredWidth: 120
                    Layout.fillHeight: true
                    color: "#FFFFFF"


                    // ========== 2. 工具栏主体（Column 纵向排列） ==========
                    Column
                    {
                        anchors.fill: parent
                        // width: 120
                        spacing: 0
                        // anchors.margins: 0

                        LeftToolBarButton
                        {
                            text: "首页"
                            btnIcon: "🏠"
                            // btnColor: "#FFFFFF"
                            // btnBorder: "#2980b9"
                            onClicked: toolBarHandler.onHomeClicked()
                        }

                        LeftToolBarButton
                        {
                            text: "多城市管理"
                            btnIcon: "⚙️"
                            // btnColor: "#9b59b6"
                            // btnBorder: "#8e44ad"
                            onClicked: toolBarHandler.onSettingsClicked()
                        }

                        LeftToolBarButton
                        {
                            text: "地图查看"
                            btnIcon: "🔍"
                            // btnColor: "#e67e22"
                            // btnBorder: "#d35400"
                            onClicked: toolBarHandler.onSearchClicked()
                        }

                        LeftToolBarButton
                        {
                            text: "天气预警"
                            btnIcon: "📊"
                            // btnColor: "#27ae60"
                            // btnBorder: "#229954"
                            onClicked: toolBarHandler.onStatisticsClicked()
                        }

                        LeftToolBarButton
                        {
                            text: "桌面小组件"
                            btnIcon: "🧩"          // 把 ❓ 换成更贴切的拼图图标
                            // btnColor: "#e74c3c"
                            // btnBorder: "#c0392b"
                            onClicked: toolBarHandler.onHelpClicked()
                        }

                        LeftToolBarButton
                        {
                            text: "历史记录"
                            btnIcon: "📜"          // ← 补上图标
                            // btnColor: "#e74c3c"
                            // btnBorder: "#c0392b"
                            onClicked: toolBarHandler.onHistoryClicked()   // 注意：这里建议单独一个槽函数
                        }
                    }
                }
                Rectangle
                {
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    color: "#E0E0E0"
                }
                // 页面容器 - 类似 QStackedWidget
                StackLayout
                {
                    id: stackLayout
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    // 安全访问 currentPage，避免 null 引用错误
                    currentIndex: toolBarHandler ? toolBarHandler.currentPage : 0

                    // 页面 0: 主页
                    HomePage
                    {
                        // anchors.fill: parent
                    }
                    // 页面 1: 设置
                    SettingsPage
                    {
                        // anchors.fill: parent
                    }
                    // 页面 2: 搜索
                    SearchPage
                    {
                        // anchors.fill: parent
                    }
                    // 页面 3: 统计
                    StatisticsPage
                    {
                        // anchors.fill: parent
                    }
                    // 页面 4: 帮助
                    HelpPage
                    {
                        // anchors.fill: parent
                    }
                }
            }
        }
    }
}
