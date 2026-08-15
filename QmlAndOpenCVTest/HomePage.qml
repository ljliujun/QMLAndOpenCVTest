import QtQuick 2.3
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import "card"

Rectangle
{
    color: "#FFFFFF"

    ColumnLayout
    {
        anchors.fill: parent
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        anchors.leftMargin: 5
        anchors.rightMargin: 10
        spacing: 10
        
        Rectangle
        {
            Layout.fillWidth: true
            height: 70
            
            color: "#FFFFFF"
            /*border.width: 1
            border.color: "#E0E0E0"
            radius:10*/

            RowLayout 
            {
                anchors.fill: parent
                anchors.bottomMargin: 15
                anchors.topMargin: 15
                anchors.leftMargin: 5
                anchors.rightMargin: 5
                spacing: 20
                Rectangle
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Text
                    {
                        text: "Hello, World!"
                    }
                }
                
                Rectangle
                {
                    
                    // Layout.fillWidth: true
                    // Layout.fillHeight: true
                    // anchors.centerIn:parent
                    width:70
                    height:35
                    border.width: 1
                    border.color: "#E0E0E0"
                    radius:10
                    Text
                    {
                        anchors.centerIn: parent
                        text: "空气优 43"
                    }
                }
                
                Item{Layout.fillWidth:true}
                Item{Layout.fillWidth:true}
                Item{Layout.fillWidth:true}
                Item{Layout.fillWidth:true}
                Item{Layout.fillWidth:true}
                Item{Layout.fillWidth:true}
            }
        }

        RowLayout
        {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 10

            WeatherCard
            {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            WeatherCard
            {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            WeatherCard
            {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            
        }

        RowLayout
        {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 10

            WeatherCard
            {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            WeatherCard
            {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }

        RowLayout
        {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 10

            WeatherCard
            {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            WeatherCard
            {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            WeatherCard
            {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }
    }
}