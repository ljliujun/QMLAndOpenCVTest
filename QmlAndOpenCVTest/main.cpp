#pragma execution_character_set("utf-8")
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlContext>
#include <QDebug>
#include <QTextStream>
#include <QTextCodec>
#include "ToolBarHandler.h"

#ifdef Q_OS_WIN
#include <windows.h>
#endif

int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN
    // 设置控制台为 UTF-8 编码,解决中文乱码问题
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    // Install a message handler so qWarning/qDebug from QML/Qt are visible in console
    qInstallMessageHandler([](QtMsgType type, const QMessageLogContext &ctx, const QString &msg)
    {
        Q_UNUSED(ctx)
        QTextStream ts(stderr);
        switch (type) 
        {
        case QtDebugMsg: ts << "Debug: " << msg << Qt::endl; break;
        case QtInfoMsg: ts << "Info: " << msg << Qt::endl; break;
        case QtWarningMsg: ts << "Warning: " << msg << Qt::endl; break;
        case QtCriticalMsg: ts << "Critical: " << msg << Qt::endl; break;
        case QtFatalMsg: ts << "Fatal: " << msg << Qt::endl; break;
        }
    });
#endif
#if defined(Q_OS_WIN) && QT_VERSION_CHECK(5, 6, 0) <= QT_VERSION && QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#endif

    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // 创建工具栏处理器并注册到 QML 上下文
    ToolBarHandler toolBarHandler;
    engine.rootContext()->setContextProperty("toolBarHandler", &toolBarHandler);

    // Helpful debug prints: show application dir and library paths
    qDebug() << "========== Application Start ==========";
    qDebug() << "ApplicationDirPath:" << QCoreApplication::applicationDirPath();
    qDebug() << "LibraryPaths:" << QCoreApplication::libraryPaths();
    qDebug() << "Qt Version:" << QT_VERSION_STR;
    qDebug() << "ToolBarHandler registered in QML context";
    qDebug() << "======================================";
    

    const QUrl url(QStringLiteral("qrc:/qt/qml/qmlandopencvtest/main.qml"));
    
    qDebug() << "Loading QML from URL:" << url.toString();
    qDebug() << "URL is valid:" << url.isValid();
    qDebug() << "URL scheme:" << url.scheme();
    qDebug() << "URL path:" << url.path();
    
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,&app, [url](const QObject *obj, const QUrl &objUrl) 
    {
        if (!obj && url == objUrl)
        {
            qCritical() << "========== FATAL ERROR: Failed to create QML object! ==========";
            qCritical() << "URL:" << url.toString();
            QCoreApplication::exit(-1);
        }
        else if (obj)
        {
            qDebug() << "QML object created successfully";
        }
    }, Qt::QueuedConnection);

    engine.load(url);
    
    qDebug() << "Root objects count:" << engine.rootObjects().size();
    
    if (engine.rootObjects().isEmpty())
    {
        qWarning() << "========== ERROR: Failed to load QML file! ==========";
        qWarning() << "Please check:";
        qWarning() << "1. QRC file is properly included in project";
        qWarning() << "2. QML file path is correct";
        qWarning() << "3. Qt modules (quick, quickcontrols2, charts) are installed";
        qWarning() << "4. Working directory is set correctly";
        return -1;
    }
    
    qDebug() << "========== Application loaded successfully ==========";

    return QApplication::exec();
}
