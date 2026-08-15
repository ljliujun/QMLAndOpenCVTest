#include "ToolBarHandler.h"

#pragma execution_character_set("utf-8")

ToolBarHandler::ToolBarHandler(QObject* parent):QObject(parent)
{
    
}

ToolBarHandler::~ToolBarHandler()
{
    
}

void ToolBarHandler::onHomeClicked()
{
    qDebug() << "C++: 主页按钮被点击";
    // setCurrentText("🏠 主页 - 欢迎回来");
    setCurrentPage(0);  // 切换到主页
    emit homeTriggered();
}

void ToolBarHandler::onSettingsClicked()
{
    qDebug() << "C++: 设置按钮被点击";
    // setCurrentText("⚙️ 设置 - 系统配置");
    setCurrentPage(1);  // 切换到设置页
    emit settingsTriggered();
}

void ToolBarHandler::onSearchClicked()
{
    qDebug() << "C++: 搜索按钮被点击";
    // setCurrentText("🔍 搜索 - 查找内容");
    setCurrentPage(2);  // 切换到搜索页
    emit searchTriggered();
}

void ToolBarHandler::onStatisticsClicked()
{
    qDebug() << "C++: 统计按钮被点击";
    // setCurrentText("📊 统计 - 数据分析");
    setCurrentPage(3);  // 切换到统计页
    emit statisticsTriggered();
}

void ToolBarHandler::onHelpClicked()
{
    qDebug() << "C++: 帮助按钮被点击";
    // setCurrentText("❓ 帮助 - 使用指南");
    setCurrentPage(4);  // 切换到帮助页
    emit helpTriggered();
}

void ToolBarHandler::setCurrentText(const QString& text)
{
    if (m_currentText != text) 
    {
        m_currentText = text;
        emit currentTextChanged(m_currentText);
    }
}

void ToolBarHandler::setCurrentPage(int page)
{
    if (m_currentPage != page) 
    {
        m_currentPage = page;
        emit currentPageChanged(m_currentPage);
    }
}
