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

    void getCurrentWeather();

signals:

    void weatherReceived(
        const QJsonObject& data);

    void errorOccurred(
        const QString& error);

private:

    QNetworkAccessManager* m_manager;
    QNetworkRequest* m_request;

    QString m_apiKey;
};