#include "Thermometre.h"

ThermometerAndHumidity::ThermometerAndHumidity() : dht(DHTPIN, DHTTYPE){
   float humidity = humidity;
   float temperature = temperature;
   DHT dht = dht;
  }

void ThermometerAndHumidity::setup(){
    Serial.begin(9600);
    dht.begin();
}

void ThermometerAndHumidity::read(){
  
}

float ThermometerAndHumidity::getTemperature(){
    temperature = dht.readTemperature();
    return temperature;
  }

float ThermometerAndHumidity::getHumidity(){
    humidity = dht.readHumidity();
    return humidity;
  }