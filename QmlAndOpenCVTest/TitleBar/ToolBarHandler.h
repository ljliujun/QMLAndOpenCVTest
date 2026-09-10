#ifndef TOOLBARHANDLER_H
#define TOOLBARHANDLER_H

#include <QDebug>
#include <QString>
#include <QObject>
#include <QWindow>

class ToolBarHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentText READ currentText NOTIFY currentTextChanged)
    Q_PROPERTY(int currentPage READ currentPage WRITE setCurrentPage NOTIFY currentPageChanged)
public:
    explicit ToolBarHandler(QObject *parent = nullptr);
    ~ToolBarHandler();
    
    QString currentText() const { return m_currentText; }
    int currentPage() const { return m_currentPage; }
    
    // 添加窗口移动方法
    Q_INVOKABLE void startWindowMove(QWindow *window, int offsetX, int offsetY);
    
public slots:
    // 主页按钮
    void onHomeClicked();

    // 设置按钮
    void onSettingsClicked();

    // 搜索按钮
    void onSearchClicked();

    // 统计按钮
    void onStatisticsClicked();

    // 帮助按钮
    void onHelpClicked();

signals:
    void homeTriggered();
    void settingsTriggered();
    void searchTriggered();
    void statisticsTriggered();
    void helpTriggered();
    void currentTextChanged(const QString &text);
    void currentPageChanged(int page);

private:
    void setCurrentText(const QString &text);
    
    void setCurrentPage(int page);
    
    QString m_currentText = "Hello World";
    int m_currentPage = 0;
};

#endif // TOOLBARHANDLER_H
