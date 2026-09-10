#include "WeatherManager.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QDateTime>
#include "WeatherDeppend/WeatherApi.h"
#include "ForecastModel.h"

WeatherManager::WeatherManager(QObject* parent)
    : QObject(parent)
    , m_weatherApi(new WeatherApi)
    , m_forecastModel(new ForecastModel(this))
{
    connect(m_weatherApi, &WeatherApi::errorOccurred, this, &WeatherManager::errorOccurred);
}

WeatherManager::~WeatherManager()
{
    delete m_weatherApi;
    m_weatherApi = nullptr;
}

void WeatherManager::setCityName(const QString& city)
{
    m_cityName = city;
    m_weatherApi->setRequestCity(city);
}

//获取当前的天气
void WeatherManager::getCurrentWeather()
{
    //请求天气数据
    const QJsonObject obj = m_weatherApi->requestWeather();

    QVariant value;
    if (m_weatherApi->getValue("cityName", value))
    {
        m_cityName = value.toString();
    }
    if (m_weatherApi->getValue("description", value))
    {
        m_description = value.toString();
    }
    if (m_weatherApi->getValue("temperature", value))
    {
        m_temperature = value.toDouble();
    }
    if (m_weatherApi->getValue("feelsLike", value))
    {
        m_feelsLike = value.toDouble();
    }
    if (m_weatherApi->getValue("humidity", value))
    {
        m_humidity = value.toInt();
    }
    if (m_weatherApi->getValue("pressure", value))
    {
        m_pressure = value.toInt();
    }
    if (m_weatherApi->getValue("windSpeed", value))
    {
        m_windSpeed = value.toDouble();
    }

    qDebug() << "Current weather updated, now fetching forecast...";
    emit weatherChanged();

    // 当前天气获取成功后，再请求预报数据
    getForecast();
}

// ---- 预报请求 ----
void WeatherManager::getForecast()
{
    if (m_cityName.isEmpty())
    {
        qWarning() << "WeatherManager: cityName is empty, skip forecast request";
        return;
    }
    const QJsonObject obj = m_weatherApi->requestForecast(40);

    QList<ForecastItem> items;
    QVariant value;
    if (m_weatherApi->getValue("forecast", value))
    {
        items = value.value<QList<ForecastItem>>();
    }
    m_forecastModel->setItems(items);

    emit forecastChanged();
}


QString WeatherManager::cityName() const   
{
    return m_cityName;
}
QString WeatherManager::description() const
{ 
    return m_description;
}

double WeatherManager::temperature() const
{ 
    return m_temperature; 
}

double WeatherManager::feelsLike() const
{ 
    return m_feelsLike;
}

int WeatherManager::humidity() const
{ 
    return m_humidity;
}

int WeatherManager::pressure() const
{ 
    return m_pressure;
}

double WeatherManager::windSpeed() const
{
    return m_windSpeed; 
}

ForecastModel* WeatherManager::forecastModel() const
{
    return m_forecastModel;
}



