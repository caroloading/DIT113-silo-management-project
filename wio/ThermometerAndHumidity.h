#ifndef wioEnvironment
#define wioEnvironment

#include "Grove_Temperature_And_Humidity_Sensor.h"
#include "TFT_eSPI.h"
#include <ctime>
#include <iostream>
#include <chrono>

//Define sensor version
#define DHTTYPE DHT11

//Define used pin
#define DHTPIN 0

class ThermometerAndHumidity{
  public:
    ThermometerAndHumidity();
    void setup();
    void loop();

  private:
    DHT dht;
    TFT_eSPI tft;
    //variables
    float humidity;
    float temperature;
}

#endif