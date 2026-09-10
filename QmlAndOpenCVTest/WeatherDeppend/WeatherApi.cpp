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
#include "ForecastModel.h"

#pragma execution_character_set("utf-8")

WeatherApi::WeatherApi(QObject* parent)
    : QObject(parent)
    , m_manager(new QNetworkAccessManager)
    , m_request(nullptr)
    , m_forecastRequest(nullptr)
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
    if (m_forecastRequest)
    {
        delete m_forecastRequest;
        m_forecastRequest = nullptr;
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
    m_requestCity = requestCity;
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
        paraWeatherJson(retJsonObjet);
        loop.quit();
    });
    loop.exec();
    
    return retJsonObjet;
}


void WeatherApi::paraWeatherJson(const QJsonObject& obj)
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

void WeatherApi::paraForecastJson(const QJsonObject& obj)
{

    m_forecastItems.clear();

    if (obj.isEmpty())
    {
        qWarning() << "WeatherManager: forecast response empty";
        return;
    }

    const QJsonArray list = obj.value("list").toArray();
    m_forecastItems.reserve(list.size());

    for (const QJsonValue& val : list)
    {
        const QJsonObject entry = val.toObject();
        
        std::shared_ptr<ForecastItem> item = std::make_shared<ForecastItem>();

        const QString dtText = entry.value("dt_txt").toString();
        if (dtText.size() >= 16)
        {
            item->timeText = dtText.mid(11, 5); // "12:00"
        }
        else
        {
            item->timeText = dtText;
        }

        // 天气描述
        const QJsonArray weatherArr = entry.value("weather").toArray();
        if (!weatherArr.isEmpty())
        {
            const QJsonObject w = weatherArr.first().toObject();
            item->description = w.value("description").toString();
            item->icon = w.value("icon").toString();
        }

        // 主数据
        const QJsonObject main = entry.value("main").toObject();
        item->temp = main.value("temp").toDouble();
        item->feelsLike = main.value("feels_like").toDouble();
        item->humidity = main.value("humidity").toInt();

        // 风速
        const QJsonObject wind = entry.value("wind").toObject();
        item->windSpeed = wind.value("speed").toDouble();

        m_forecastItems.append(item);
    }
}

bool WeatherApi::getValue(const QString& name, QVariant& value) const
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
    else if (name == "forecast")
    {
        QList<ForecastItem> forecastItems;
        for (const auto& item : m_forecastItems)
        {
            forecastItems.append(*item);
        }
        value = QVariant::fromValue(forecastItems);
    }
    else
    {
        return false;
    }

    return true;
}

QNetworkRequest WeatherApi::buildForecastRequest(const QString& city, int cnt)
{
    QUrl url("https://cn-api.openweathermap.org/data/2.5/forecast");
    QUrlQuery query;
    query.addQueryItem("q", city);
    query.addQueryItem("appid", m_apiKey);
    query.addQueryItem("units", "metric");
    query.addQueryItem("lang", "zh_cn");
    query.addQueryItem("cnt", QString::number(cnt));
    url.setQuery(query);

    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::UserAgentHeader, "WeatherStudio/1.0");
    return req;
}

QJsonObject WeatherApi::requestForecast(int cnt)
{
    if (!m_manager || m_requestCity.isEmpty())
    {
        qWarning() << "requestForecast: requestCity is empty, skip";
        return {};
    }

    qDebug() << "requestForecast: requesting forecast for" << m_requestCity << "cnt=" << cnt;

    if (m_forecastRequest)
    {
        delete m_forecastRequest;
        m_forecastRequest = nullptr;
    }
    m_forecastRequest = new QNetworkRequest(buildForecastRequest(m_requestCity, cnt));

    QJsonObject retObj;
    QEventLoop loop;
    QNetworkReply* reply = m_manager->get(*m_forecastRequest);

    connect(reply, &QNetworkReply::finished, this, [this,reply, &retObj, &loop]
        {
            reply->deleteLater();
            if (reply->error() != QNetworkReply::NoError)
            {
                qWarning() << "requestForecast error:" << reply->errorString();
                loop.quit();
                return;
            }
            QJsonParseError parseError;
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll(), &parseError);
            if (parseError.error != QJsonParseError::NoError || !document.isObject())
            {
                qWarning() << "requestForecast JSON parse error:" << parseError.errorString();
                loop.quit();
                return;
            }
            retObj = document.object();
            paraForecastJson(retObj);
            loop.quit();
        });

    loop.exec();
    return retObj;
}


