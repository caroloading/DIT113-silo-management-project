#include "ThermometerAndHumidity.h"

wioEnvironment::wioEnvironment() : dht(DHTPIN, DHTTYPE){
}

void wioEnvironment::setup(){
    Serial.begin(9600);
    dht.begin();
    tft.begin();
    tft.setRotation(3);
    tft.setCursor(0, 0);
    tft.setTextFont(4);
}

void wioEnvironment::loop(){
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
    delay(30000);
}

