import QtQuick 2.3
import QtQuick.Layouts 1.15

Rectangle {
    color: "#FFFFFF"

    property string cardTitle: ""
    property string cardValue: ""

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 4

        Text {
            text: cardTitle
            font.pointSize: 9
            color: "#999999"
            Layout.alignment: Qt.AlignHCenter
        }
        Text {
            text: cardValue
            font.pointSize: 13
            font.bold: true
            color: "#222222"
            Layout.alignment: Qt.AlignHCenter
        }
    }
}
