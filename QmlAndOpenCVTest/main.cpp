#include <QGuiApplication>
#include <QTextCodec>
#include "ToolBarHandler.h"
#include "QmlEnginManager.h"
#include "WeatherDeppend/WeatherManager.h"

#ifdef Q_OS_WIN
#include <windows.h>
#endif

#pragma execution_character_set("utf-8")

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
    
    // 创建 QmlEnginManager 实例
    QmlEnginManager enginManager(app);

    /*WeatherApi weather;
    weather.setRequestCity("shenzhen");
    weather.getCurrentWeather();#1#*/
    WeatherManager weatherManager;
    weatherManager.setCityName("shenzhen");
    return QApplication::exec();
}
