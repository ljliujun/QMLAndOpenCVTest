#pragma once

#include <QApplication>

class QQmlApplicationEngine;

class QmlEnginManager
{
public:
    QmlEnginManager(const QApplication &app);
    ~QmlEnginManager();
    void loadQml(const QApplication& app);

private:
    void registCppClassToQml() const;
private:
    QQmlApplicationEngine *m_engine;
};

