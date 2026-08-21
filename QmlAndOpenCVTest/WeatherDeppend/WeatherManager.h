#pragma once
#include <QObject>

class WeatherApi;
class WeatherManager : public QObject
{
public:
    WeatherManager(QObject* parent = nullptr);
    ~WeatherManager() override;
    void setCityName(const QString& city);
    void getCurrentWeather() const;

private:
    WeatherApi* m_weatherApi;
};

