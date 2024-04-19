#ifndef wioEnvironment
#define wioEnvironment

#include "Grove_Temperature_And_Humidity_Sensor.h"
#include "TFT_eSPI.h"

//Define sensor version
#define DHTTYPE DHT11

//Define used pin
#define DHTPIN PIN_WIRE_SCL

class ThermometerAndHumidity{
  public:
    ThermometerAndHumidity();
    const char* convertReadings();
    float getTemperature();
    float getHumidity();

  private:
    DHT dht;
    TFT_eSPI tft;
    //variables
    float humidity;
    float temperature;
};

#endif