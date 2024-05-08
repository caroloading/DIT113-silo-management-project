#include "ThermometerAndHumidity.h"


ThermometerAndHumidity::ThermometerAndHumidity() : _dht(DHT_PIN, DHT_TYPE) { }

double ThermometerAndHumidity::GetTemperature()
{
    double temperature = _dht.readTemperature(); // returns NaN when sensor is not connected

    return std::isnan(temperature) ? 0.00 : temperature;
}

double ThermometerAndHumidity::GetHumidity()
{
    double humidity = _dht.readHumidity();

    return humidity;
}

