#include "WeatherManager.h"
#include <windows.h>
#include <QTimer>
#include "WeatherDeppend/WeatherApi.h"

WeatherManager::WeatherManager(QObject* parent)
    : QObject(parent)
    , m_weatherApi(new WeatherApi)
{
}

WeatherManager::~WeatherManager()
{
    
}
void WeatherManager::setCityName(const QString& city)
{
    m_weatherApi->setRequestCity(city);
    
    /*QTimer *timer = new QTimer;
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, [this]
    {
        getCurrentWeather();
    });
    
    timer->start();*/
}

void WeatherManager::getCurrentWeather() const
{
    m_weatherApi->getCurrentWeather();
}



