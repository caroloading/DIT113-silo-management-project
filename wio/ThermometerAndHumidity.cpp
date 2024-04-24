#include "ThermometerAndHumidity.h"


ThermometerAndHumidity::ThermometerAndHumidity() : dht(DHTPIN, DHTTYPE)
{
   _humidity = humidity;
   _temperature = temperature;
   _dht = dht;
   _tft = tft;
}

const char* ThermometerAndHumidity::ConvertReadings()
{
  String convertedTemperature = String(GetTemperature());
  String convertedHumidity = String(getHumidity());

  String environmentReadings = ""+convertedTemperature +"C "+ convertedHumidity+"% ";

  return environmentReadings.c_str();
}

long ThermometerAndHumidity::GetTemperature()
{
  long temperature = dht.readTemperature();

  return temperature;
}

long ThermometerAndHumidity::GetHumidity()
{
  long humidity = dht.readHumidity();

  return humidity;
}

std::string ThermometerAndHumidity::GetTempData()
{
    return "{\"value\": " + std::to_string(GetTemperature()) + "}";
}

std::string ThermometerAndHumidity::GetHumidityData()
{
    return "{\"value\": " + std::to_string(GetHumidity()) + "}";
}
