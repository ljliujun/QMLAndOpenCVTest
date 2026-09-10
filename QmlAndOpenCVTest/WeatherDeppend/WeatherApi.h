#pragma once

#include <QObject>
#include <QNetworkAccessManager>

struct ForecastItem;

class WeatherApi : public QObject
{
    Q_OBJECT

public:
    explicit WeatherApi(QObject* parent = nullptr);
    ~WeatherApi();
    void setRequestCity(const QString& requestCity);
    void initRequest(const QString& requestCity);
    QJsonObject requestWeather();
    // 5天/3小时 预报请求（返回 /data/2.5/forecast 的完整 JSON）
    QJsonObject requestForecast(int cnt = 40);

    //解析请求到的数据
    void paraWeatherJson(const QJsonObject& obj);
    void paraForecastJson(const QJsonObject& QJsonObject);
    bool getValue(const QString& name, QVariant& value) const;
signals:

    void weatherReceived(const QJsonObject& data);

    void errorOccurred(const QString& error);
private:
    // 根据城市名构造预报 API URL
    QNetworkRequest buildForecastRequest(const QString& city, int cnt);
private:

    QNetworkAccessManager* m_manager;
    QNetworkRequest* m_request; // 当前天气请求
    QNetworkRequest* m_forecastRequest;  // 预报请求

    QString m_apiKey;

    QString m_requestCity;   // 调用方请求的城市名（setRequestCity 时设置）
    QString m_cityName;      // API 响应返回的城市名
    QString m_description;
    double  m_temperature = 0.0;
    double  m_feelsLike = 0.0;
    int     m_humidity = 0;
    int     m_pressure = 0;
    double  m_windSpeed = 0.0;

    QList<std::shared_ptr<ForecastItem>> m_forecastItems;
};