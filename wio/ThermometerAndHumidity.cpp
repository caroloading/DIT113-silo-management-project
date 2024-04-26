#include "ThermometerAndHumidity.h"


ThermometerAndHumidity::ThermometerAndHumidity() : _dht(DHT_PIN, DHT_TYPE) { }

const char* ThermometerAndHumidity::ConvertReadings()
{
    // NOTE: allocate memory on the heap instead of the stack to avoid potential
    // problems of loosing the data once the 'readingsBuffer' goes out of scope.
    char* readingsBuffer = new char[50];

    long temperatures = GetTemperature();
    long humidity = GetHumidity();

    std::sprintf(readingsBuffer, "%ldC %ld%%", temperatures, humidity);
    
    return readingsBuffer;
}

long ThermometerAndHumidity::GetTemperature()
{
    long temperature = _dht.readTemperature();

    return temperature;
}

long ThermometerAndHumidity::GetHumidity()
{
    long humidity = _dht.readHumidity();

    return humidity;
}

