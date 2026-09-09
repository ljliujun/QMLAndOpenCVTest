#pragma once
#include <QObject>

class WeatherApi;
class WeatherManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString cityName   READ cityName   NOTIFY weatherChanged)
    Q_PROPERTY(QString description READ description NOTIFY weatherChanged)
    Q_PROPERTY(double  temperature READ temperature NOTIFY weatherChanged)
    Q_PROPERTY(double  feelsLike   READ feelsLike   NOTIFY weatherChanged)
    Q_PROPERTY(int     humidity    READ humidity    NOTIFY weatherChanged)
    Q_PROPERTY(int     pressure    READ pressure    NOTIFY weatherChanged)
    Q_PROPERTY(double  windSpeed   READ windSpeed   NOTIFY weatherChanged)

public:
    explicit WeatherManager(QObject* parent = nullptr);
    ~WeatherManager() override;

    QString cityName() const;
    QString description() const;
    double  temperature() const;
    double  feelsLike() const;
    int     humidity() const;
    int     pressure() const;
    double  windSpeed() const;

    void setCityName(const QString& city);
    Q_INVOKABLE void getCurrentWeather();

signals:
    void weatherChanged();
    void errorOccurred(const QString& error);

private:
    WeatherApi* m_weatherApi = nullptr;

    QString m_cityName;
    QString m_description;
    double  m_temperature = 0.0;
    double  m_feelsLike   = 0.0;
    int     m_humidity    = 0;
    int     m_pressure    = 0;
    double  m_windSpeed   = 0.0;
};

