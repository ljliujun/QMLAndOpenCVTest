#include "QmlEnginManager.h"
#include <QQmlApplicationEngine>
#include <QCoreApplication>
#include <QQmlContext>
#include "ToolBarHandler.h"


QmlEnginManager::QmlEnginManager(const QApplication &app)
    : m_engine(new QQmlApplicationEngine)
{
    loadQml(app);
    registCppClassToQml();
}

QmlEnginManager::~QmlEnginManager()
= default;

void QmlEnginManager::loadQml(const QApplication &app)
{
    const QUrl url(QStringLiteral("qrc:/qt/qml/qmlandopencvtest/main.qml"));
    
    qDebug() << "Loading QML from URL:" << url.toString();
    qDebug() << "URL is valid:" << url.isValid();
    qDebug() << "URL scheme:" << url.scheme();
    qDebug() << "URL path:" << url.path();
    
    QObject::connect(m_engine, &QQmlApplicationEngine::objectCreated,&app, [url](const QObject *obj, const QUrl &objUrl) 
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

    m_engine->load(url);
    
    qDebug() << "Root objects count:" << m_engine->rootObjects().size();
    
    if (m_engine->rootObjects().isEmpty())
    {
        qWarning() << "========== ERROR: Failed to load QML file! ==========";
        qWarning() << "Please check:";
        qWarning() << "1. QRC file is properly included in project";
        qWarning() << "2. QML file path is correct";
        qWarning() << "3. Qt modules (quick, quickcontrols2, charts) are installed";
        qWarning() << "4. Working directory is set correctly";
        return;
    }
    
    qDebug() << "========== Application loaded successfully ==========";
}

void QmlEnginManager::registCppClassToQml() const
{
    // 创建工具栏处理器并注册到 QML 上下文
    ToolBarHandler* toolBarHandler = new ToolBarHandler;
    
    qDebug() << "Creating ToolBarHandler instance at:" << toolBarHandler;
    m_engine->rootContext()->setContextProperty("toolBarHandler", toolBarHandler);
    
    // 验证是否注册成功
    QVariant contextProp = m_engine->rootContext()->contextProperty("toolBarHandler");
    if (contextProp.isValid() && !contextProp.isNull()) {
        qDebug() << "ToolBarHandler registered successfully in QML context";
    } else {
        qWarning() << "Failed to register ToolBarHandler! Context property is invalid or null";
    }

    // Helpful debug prints: show application dir and library paths
    qDebug() << "========== Application Start ==========";
    qDebug() << "ApplicationDirPath:" << QCoreApplication::applicationDirPath();
    qDebug() << "LibraryPaths:" << QCoreApplication::libraryPaths();
    qDebug() << "Qt Version:" << QT_VERSION_STR;
    qDebug() << "ToolBarHandler registered in QML context";
    qDebug() << "======================================";
}
