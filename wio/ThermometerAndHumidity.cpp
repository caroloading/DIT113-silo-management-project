#include "ThermometerAndHumidity.h"


ThermometerAndHumidity::ThermometerAndHumidity() : _dht(DHT_PIN, DHT_TYPE) { }

double ThermometerAndHumidity::GetTemperature()
{
    double temperature = _dht.readTemperature();

    return temperature;
}

double ThermometerAndHumidity::GetHumidity()
{
    double humidity = _dht.readHumidity();

    return humidity;
}

