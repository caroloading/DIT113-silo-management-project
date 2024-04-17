#include "Thermometre.h"

ThermometerAndHumidity::ThermometerAndHumidity() : dht(DHTPIN, DHTTYPE){
   float humidity = humidity;
   float temperature = temperature;
   DHT dht = dht;
   TFT_eSPI tft = tft;
  }

void ThermometerAndHumidity::setup(){
    Serial.begin(9600);
    dht.begin();
    tft.begin();
    tft.setRotation(3);
    tft.setCursor(50,100);
    tft.setTextColor(TFT_BLACK, TFT_RED);          //sets the text colour to black
    tft.setTextSize(5);
    tft.fillScreen(TFT_RED);
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