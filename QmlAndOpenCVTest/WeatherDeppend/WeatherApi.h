#pragma once

#include <QObject>
#include <QNetworkAccessManager>

class WeatherApi : public QObject
{
    Q_OBJECT

public:
    explicit WeatherApi(QObject* parent = nullptr);
    ~WeatherApi();
    void setRequestCity(const QString& requestCity);
    void initRequest(const QString& requestCity);
    QJsonObject requestWeather();
    //解析请求到的数据
    void paraWeatherJson(const QJsonObject& obj);

    bool getValue(const QString& name, QVariant& value) const;
signals:

    void weatherReceived(const QJsonObject& data);

    void errorOccurred(const QString& error);

private:

    QNetworkAccessManager* m_manager;
    QNetworkRequest* m_request;

    QString m_apiKey;

    QString m_cityName;
    QString m_description;
    double  m_temperature = 0.0;
    double  m_feelsLike = 0.0;
    int     m_humidity = 0;
    int     m_pressure = 0;
    double  m_windSpeed = 0.0;
};