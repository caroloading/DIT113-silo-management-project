#include "ThermometerAndHumidity.h"

ThermometerAndHumidity::ThermometerAndHumidity() : dht(DHTPIN, DHTTYPE){
   long humidity = humidity;
   long temperature = temperature;
   DHT dht = dht;
   TFT_eSPI tft = tft;
}

const char* ThermometerAndHumidity::convertReadings(){
  String convertedTemperature = String(getTemperature());
  String convertedHumidity = String(getHumidity());

  String environmentReadings = ""+convertedTemperature +"C "+ convertedHumidity+"% ";
  return environmentReadings.c_str();
}

long ThermometerAndHumidity::getTemperature(){
  long temperature = dht.readTemperature();
  return temperature;
}

long ThermometerAndHumidity::getHumidity(){
  long humidity = dht.readHumidity();
  return humidity;
}

std::string ThermometerAndHumidity::getTempData(){
    return "{\"value\": " + std::to_string(getTemperature()) + "}";
}

std::string ThermometerAndHumidity::getHumidityData(){
    return "{\"value\": " + std::to_string(getHumidity()) + "}";
}