import QtQuick 2.3
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

WeatherCard
{
    id: mainWeatherCard

    ColumnLayout
    {
        anchors.bottomMargin: 10
        anchors.topMargin: 15
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.fill: parent
        spacing:0

        RowLayout
        {
            Layout.preferredHeight: 2
            anchors.fill: parent
            spacing:10

            Rectangle
            {
                Layout.preferredWidth: 3
                Layout.fillWidth:true
                Layout.fillHeight:true
                Text
                {
                    anchors.centerIn: parent
                    text: "天气图片"
                }
            }
            ColumnLayout
            {
                Layout.preferredWidth: 3
                Rectangle
                {
                    Layout.fillWidth:true
                    Layout.fillHeight:true
                    Text
                    {
                        Layout.preferredHeight: 3
                        anchors.centerIn: parent
                        font.pointSize: 30       // 像素大小，可根据需要调整
                        font.bold: true          // 加粗（或使用 font.weight: Font.Bold）
                        text: "28℃"
                    }
                }
                Rectangle
                {
                    Layout.preferredHeight: 1
                    Layout.fillWidth:true
                    Layout.fillHeight:true
                    Text
                    {
                        anchors
                        {
                            top: parent.top
                            topMargin: 0           // 距离顶部的边距（可选）
                            horizontalCenter: parent.horizontalCenter
                        }
                        font.pointSize: 10       // 像素大小，可根据需要调整
                        text: "体感温度 29℃"
                    }
                }
            }
            Rectangle
            {
                Layout.preferredWidth: 1
                Layout.fillWidth:true
                Layout.fillHeight:true
                Text
                {
                    anchors
                    {
                        left: parent.left
                        leftMargin: 10          // 距离左边缘的间距，可根据需要调整
                        verticalCenter: parent.verticalCenter
                    }
                    font.pointSize: 13       // 像素大小，可根据需要调整
                    text: "晴"
                }
            }
        }
        
        WeatherCard
        {
            Layout.preferredHeight: 1
            Layout.fillWidth:true
            Layout.fillHeight:true
        }
    }
}