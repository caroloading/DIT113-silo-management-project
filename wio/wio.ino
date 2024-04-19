#include <DateTime.h>
#include <RTC_SAMD51.h>

#include "Thermometre.h"
#include "TFT_eSPI.h"
#include "MqttBroker.h"
#include "secrets.h"
#include "CustomWiFi.h"

TFT_eSPI tft;
RTC_SAMD51 rtc;
#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD

CustomWiFi wifi(ssid, password);
MqttClient mqtt();

ThermometerAndHumidity thermometerhumidity;

void setup(){
  thermometerhumidity.setup();
  rtc.begin();
  DateTime now = DateTime(F(__DATE__), F(__TIME__));
  rtc.adjust(now);
  tft.begin();
  tft.setRotation(3);
  tft.setCursor(50,100);
  tft.setTextColor(TFT_BLACK);          //sets the text colour to black
  tft.setTextSize(2);
  tft.fillScreen(TFT_RED);
  tft.println("connecting to wifi..");

  Serial.begin(115200);
  wifi.connectToWiFi();
  if(wifi.getWiFiStatus() == true){
    tft.fillScreen(TFT_GREEN);
    tft.println("connected to wifi");
    tft.println("IP Adress: "+ WiFi.localIP().toString());
  }
  mqtt.connect(); // Connect the MQTT Server
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

    while(wifi.getWiFiStatus() != true){
    tft.println("connecting to wifi");
    wifi.connectToWiFi();
}

mqtt.publish("wio/temperature","23.01/2024-04-17 09:23:21");//publishes to the broker
mqtt.publish("wio/distance","12.3/2024-04-17 09:24:22");
mqtt.publish("wio/humidity","58.00/2024-04-17 09:24:22");
delay(15000);
  }


