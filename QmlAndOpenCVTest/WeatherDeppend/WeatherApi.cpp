#include "WeatherApi.h"
#include <QJsonArray>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSslSocket>
#include <QDebug>
#include <QEventLoop>

#pragma execution_character_set("utf-8")

WeatherApi::WeatherApi(QObject* parent)
    : QObject(parent)
    , m_manager(new QNetworkAccessManager)
    , m_request(nullptr)
{
    m_apiKey = "874084ed8d8544487e165b13eb45809c";
}

WeatherApi::~WeatherApi()
{
    if (m_request)
    {
        delete m_request;
        m_request = nullptr;
    }
    if (m_manager)
    {
        delete m_manager;
        m_manager = nullptr;
    }
}

void WeatherApi::setRequestCity(const QString& requestCity)
{
    initRequest(requestCity);
}

void WeatherApi::initRequest(const QString& requestCity)
{
    qDebug() << "SSL supported:"
             << QSslSocket::supportsSsl();

    qDebug() << "Build SSL:"
             << QSslSocket::sslLibraryBuildVersionString();

    qDebug() << "Runtime SSL:"
             << QSslSocket::sslLibraryVersionString();
    
    QUrl url("https://cn-api.openweathermap.org/data/2.5/weather");

    QUrlQuery query;

    query.addQueryItem("q",requestCity);

    query.addQueryItem("appid",m_apiKey);

    query.addQueryItem("units","metric");

    query.addQueryItem("lang","zh_cn");

    url.setQuery(query);
    
    if (m_request)
    {
        delete m_request;
        m_request = nullptr;
    }
    m_request = new QNetworkRequest(url);
    m_request->setHeader(QNetworkRequest::UserAgentHeader,"WeatherStudio/1.0");
}

QJsonObject WeatherApi::requestWeather()
{
    if (!m_manager)
        return {};
    if (!m_request)
    {
        qWarning() << "Request is not initialized";
        return {};
    }
        
    QJsonObject retJsonObjet;   //存放请求的结果
    QEventLoop loop;
    QNetworkReply* reply = m_manager->get(*m_request);
    connect(reply, &QNetworkReply::finished, this, [this, reply, &retJsonObjet,&loop]
    {
        reply->deleteLater();
        if (reply->error() != QNetworkReply::NoError)
        {
            emit errorOccurred(reply->errorString());
            qDebug() <<"error = "<< reply->errorString();
            return;
        }
        QByteArray data = reply->readAll();

        /*qDebug() << "========== Raw Response Data ==========";
        qDebug() << QString::fromUtf8(data);
        qDebug() << "=======================================";*/

        QJsonParseError parseError;

        QJsonDocument document = QJsonDocument::fromJson(data,&parseError);

        if (parseError.error != QJsonParseError::NoError)
        {
            qWarning() << "JSON Parse Error:" << parseError.errorString();
            return;
        }
        
        if (!document.isObject())
        {
            qWarning() << "Response is not a JSON object";
            return;
        }
        retJsonObjet = document.object();
        loop.quit();
    });
    loop.exec();
    
    return retJsonObjet;
}


void WeatherApi::getCurrentWeather()
{
    
    const auto requestJsonObj = requestWeather();
    
    qDebug() << "========== Parsed Weather Data ==========";
    qDebug() << "City:" << requestJsonObj.value("name").toString();
            
    if (requestJsonObj.contains("weather")) 
    {
        QJsonArray weatherArray = requestJsonObj.value("weather").toArray();
        if (!weatherArray.isEmpty())
        {
            QJsonObject weather = weatherArray.first().toObject();
            qDebug() << "Weather:" << weather.value("description").toString();
            qDebug() << "Weather Main:" << weather.value("main").toString();
        }
    }
            
    if (requestJsonObj.contains("main"))
    {
        QJsonObject main = requestJsonObj.value("main").toObject();
        qDebug() << "Temperature:" << main.value("temp").toDouble() << "°C";
        qDebug() << "Feels Like:" << main.value("feels_like").toDouble() << "°C";
        qDebug() << "Humidity:" << main.value("humidity").toInt() << "%";
        qDebug() << "Pressure:" << main.value("pressure").toInt() << "hPa";
    }
            
    if (requestJsonObj.contains("wind")) 
    {
        QJsonObject wind = requestJsonObj.value("wind").toObject();
        qDebug() << "Wind Speed:" << wind.value("speed").toDouble() << "m/s";
    }
            
    qDebug() << "=======================================";
}