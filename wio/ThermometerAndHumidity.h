#ifndef wioEnvironment
#define wioEnvironment

#include <iostream>
#include "Grove_Temperature_And_Humidity_Sensor.h"
#include "TFT_eSPI.h"

#define DHT_TYPE DHT11
#define DHT_PIN PIN_WIRE_SCL


class ThermometerAndHumidity
{
  public:
    ThermometerAndHumidity();
    const char* ConvertReadings();
    std::string GetTempData();
    std::string GetHumidityData();
    long        GetTemperature();
    long        GetHumidity();

  private:
    DHT      _dht;
    TFT_eSPI _tft;

    long _humidity;
    long _temperature;
};

#endif
