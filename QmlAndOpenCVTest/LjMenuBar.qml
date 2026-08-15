import QtQuick 2.3
import QtQuick.Controls 2.15

MenuBar
{
    id: menuBar
    background: Rectangle
    {
        color: "#cccccc"
        implicitHeight: 30      // 可选，控制高度
    }
    GlobalMenu
    {
        title: "文件"
        Action
        {
            text: "打开"
            onTriggered:
            {
                console.log("菜单：打开文件")
                // TODO: 实现打开文件功能
            }
        }
        Action
        {
            text: "保存"
            onTriggered:
            {
                console.log("菜单：保存文件")
                // TODO: 实现保存文件功能
            }
        }
        // MenuSeparator{}
        Action
        {
            text: "退出"
            onTriggered:
            {
                console.log("菜单：退出程序")
                Qt.quit()
            }
        }
    }
    GlobalMenu
    {
        title: "编辑"
        Action
        {
            text: "剪切"
            onTriggered:
            {
                console.log("菜单：剪切")
                // TODO: 实现剪切功能
            }
        }
        Action
        {
            text: "复制"
            onTriggered:
            {
                console.log("菜单：复制")
                // TODO: 实现复制功能
            }
        }
        Action
        {
            text: "粘贴"
            onTriggered:
            {
                console.log("菜单：粘贴")
                // TODO: 实现粘贴功能
            }
        }
    }
}