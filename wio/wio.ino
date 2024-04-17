#include <DateTime.h>
#include <RTC_SAMD51.h>

#include "Thermometre.h"
#include "TFT_eSPI.h"

TFT_eSPI tft;
RTC_SAMD51 rtc;

ThermometerAndHumidity thermometerhumidity;

void setup(){
  thermometerhumidity.setup();
  rtc.begin();
  DateTime now = DateTime(F(__DATE__), F(__TIME__));
  rtc.adjust(now);
  }

  

void loop(){
  DateTime now = rtc.now();
  tft.setTextSize(1);
    float tempreading = thermometerhumidity.getTemperature();
    float humreading = thermometerhumidity.getHumidity();

    //mqtt.publish
    //mqtt.publish
    
    if(tempreading < 20.0 || tempreading > 35.0){
        tft.println("WARNING: Temperature out of bounds!!!");
    }
    else if(humreading < 25.0 || humreading > 40.0){
        tft.println("WARNING: Humidity out of bounds!!!");
    }else{
        tft.print(thermometerhumidity.convertReadings());
        tft.print(" Date: ");
        tft.print(now.year(), DEC);
        tft.print('/');
        tft.print(now.month(), DEC);
        tft.print('/');
        tft.print(now.day(), DEC);
        tft.print("   ");
        tft.print(now.hour(), DEC);
        tft.print(':');
        tft.print(now.minute(), DEC);
        tft.println();  
    } 
    delay(10000);
    tft.setCursor(0,0);
    tft.fillScreen(TFT_RED);
  }