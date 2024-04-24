#ifndef wioEnvironment
#define wioEnvironment

#include <iostream>
#include "Grove_Temperature_And_Humidity_Sensor.h"
#include "TFT_eSPI.h"

#include <RTC_SAMD51.h>

//Define sensor version
#define DHTTYPE DHT11

//Define used pin
#define DHTPIN PIN_WIRE_SCL

class ThermometerAndHumidity{
  public:
    ThermometerAndHumidity();
    const char* convertReadings();
    std::string getTempData();
    std::string getHumidityData();
    long getTemperature();
    long getHumidity();

  private:
    DHT dht;
    TFT_eSPI tft;
    //variables
    long humidity;
    long temperature;
};

#endif