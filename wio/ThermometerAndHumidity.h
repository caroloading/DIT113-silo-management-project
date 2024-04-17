#ifndef wioEnvironment
#define wioEnvironment

#include "Grove_Temperature_And_Humidity_Sensor.h"
#include "TFT_eSPI.h"

//Define sensor version
#define DHTTYPE DHT11

//Define used pin
#define DHTPIN 0

class ThermometerAndHumidity{
  public:
    ThermometerAndHumidity();
    void setup();
    void read();
    float getTemperature();
    float getHumidity();

  private:
    DHT dht;
    //variables
    float humidity;
    float temperature;
};

#endif