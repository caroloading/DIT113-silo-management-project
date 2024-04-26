#include "ThermometerAndHumidity.h"

extern RTC_SAMD51 rtc;

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
  std::string now = std::string(rtc.now().timestamp(DateTime::TIMESTAMP_FULL).c_str());  // ISO_LOCAL_DATE_TIME
  return "{\"value\": " + std::to_string(getTemperature()) + ", \"dateTime\": \"" + now + "\"}";
}

std::string ThermometerAndHumidity::getHumidityData(){
  std::string now = std::string(rtc.now().timestamp(DateTime::TIMESTAMP_FULL).c_str()); // ISO_LOCAL_DATE_TIME
  return "{\"value\": " + std::to_string(getHumidity()) + ", \"dateTime\": \"" + now + "\"}";
}