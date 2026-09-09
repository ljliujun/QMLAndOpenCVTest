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
        //解析天气数据
        paraWeatheJson(retJsonObjet);
        loop.quit();
    });
    loop.exec();
    
    return retJsonObjet;
}


void WeatherApi::paraWeatheJson(const QJsonObject& obj)
{
    if (obj.isEmpty())
    {
        qWarning() << "WeatherManager: empty response, skip update";
        return;
    }
    m_cityName = obj.value("name").toString();

    const QJsonArray weatherArray = obj.value("weather").toArray();
    if (!weatherArray.isEmpty())
    {
        m_description = weatherArray.first().toObject()
            .value("description").toString();
    }

    const QJsonObject main = obj.value("main").toObject();

    m_temperature = main.value("temp").toDouble();

    m_feelsLike = main.value("feels_like").toDouble();

    m_humidity = main.value("humidity").toInt();

    m_pressure = main.value("pressure").toInt();

    const QJsonObject wind = obj.value("wind").toObject();
    m_windSpeed = wind.value("speed").toDouble();

}

bool WeatherApi::getValue(const QString& name, QVariant& value)
{
    if (name == "cityName")
    {
        value = m_cityName;
    }
    else if (name == "description")
    {
        value = m_description;
    }
    else if (name == "temperature")
    {
        value = m_temperature;
    }
    else if (name == "feelsLike")
    {
        value = m_feelsLike;
    }
    else if (name == "humidity")
    {
        value = m_humidity;
    }
    else if (name == "pressure")
    {
        value = m_pressure;
    }
    else if (name == "windSpeed")
    {
        value = m_windSpeed;
    }
    else
    {
        return false;
    }

    return true;
}