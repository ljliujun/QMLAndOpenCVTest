// import QtQuick 2.15
// import QtQuick.Controls 2.15   // 关键修改
//
// Menu
// {
//     background: Rectangle
//     {
//         width: 200
//         height: 200
//         color: "gray"
//         radius: 4
//     }
// }

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

Menu
{
    id: globalMenu
    delegate: GlobalMenuItem {}
    background: Rectangle
    {
        implicitWidth: 200
        // implicitHeight: 30
        color: "#f0f0f0"
        border.color: "#cccccc"
        radius: 4
    }
    
    // separator: MenuSeparator {
    //     background: Rectangle {
    //         anchors.left: parent.left
    //         anchors.right: parent.right
    //         height: 1
    //         color: "#cccccc"
    //     }
    // }

    contentItem: ListView
    {
        implicitHeight: contentHeight
        model: globalMenu.contentModel
        interactive: Window.window ? contentHeight > Window.window.height : false
        clip: true

        Rectangle
        {
            anchors.fill: parent
            color: "transparent"
        }
    }
}
