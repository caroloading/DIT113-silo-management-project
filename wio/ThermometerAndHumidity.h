#ifndef wioEnvironment
#define wioEnvironment

#include <iostream>
#include "Grove_Temperature_And_Humidity_Sensor.h"
#include "JsonSerializable.h"

#define DHT_TYPE DHT11
#define DHT_PIN PIN_WIRE_SCL


class ThermometerAndHumidity : public JsonSerializable
{
    public:
        ThermometerAndHumidity();
        const char* ConvertReadings();
        double        GetTemperature();
        double        GetHumidity();
    private:
        DHT  _dht;
        double _humidity;
        double _temperature;
};


#endif

