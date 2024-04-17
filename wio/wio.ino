#include "Thermometre.h"

ThermometerAndHumidity thermometerhumidity;

void setup(){
  thermometerhumidity.setup();
  }

void loop(){
    Serial.println(thermometerhumidity.getTemperature());
    Serial.println(thermometerhumidity.getHumidity());
    delay(1000);
  }
