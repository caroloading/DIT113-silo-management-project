#include "ThermometerAndHumidity.h"

ThermometerAndHumidity::ThermometerAndHumidity() : dht(DHTPIN, DHTTYPE){
   float humidity = humidity;
   float temperature = temperature;
   DHT dht = dht;
   TFT_eSPI tft = tft;
}

const char* ThermometerAndHumidity::convertReadings(){
  String convertedTemperature = String(getTemperature());
  String convertedHumidity = String(getHumidity());

  String environmentReadings = ""+convertedTemperature +"C "+ convertedHumidity+"% ";
  return environmentReadings.c_str();
}

float ThermometerAndHumidity::getTemperature(){
  float temperature = dht.readTemperature();
  return temperature;
}

float ThermometerAndHumidity::getHumidity(){
  float humidity = dht.readHumidity();
  return humidity;
}