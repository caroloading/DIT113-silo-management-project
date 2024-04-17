#include "Thermometre.h"
#include "TFT_eSPI.h"

TFT_eSPI tft;

ThermometerAndHumidity thermometerhumidity;

void setup(){
  thermometerhumidity.setup();
  }

void loop(){
  tft.setTextSize(8);
    float tempreading = thermometerhumidity.getTemperature();
    float humreading = thermometerhumidity.getHumidity();

    //mqtt.publish
    //mqtt.publish
    
    if(tempreading > 20.0 && tempreading < 35.0){
        tft.println(tempreading);
     }
    else{
        tft.println("WARNING: Temperature out of bounds!!!");
     }
  
    if(humreading > 25.0 && humreading < 40.0){
        tft.println(humreading);
     }
    else{
        tft.println("WARNING: Humidity out of bounds!!!");
     }
     
    delay(1000);
    tft.setCursor(0,0);
    tft.fillScreen(TFT_RED);
  }