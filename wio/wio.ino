#include "MqttBroker.h"
#include "TFT_eSPI.h"
#include "secrets.h"
#include "CustomWiFi.h"


#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD

TFT_eSPI tft;
CustomWiFi wifi(ssid, password);
MqttBroker mqtt("broker.mqtt-dashboard.com");

void setup() {
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
    tft.println("connected to wifi");
    tft.println("IP Adress: "+ WiFi.localIP().toString());
  }
  mqtt.connect(); // Connect the MQTT Server
    
 
}

void loop() {
while(wifi.getWiFiStatus() != true){
    tft.println("connecting to wifi");
    wifi.connectToWiFi();
}

//mqtt.publish("wio/temperature",temperature);//publishes to the broker
//mqtt.publish("wio/heigth",heigth);
//mqtt.publish("wio/humidity",humidity);
delay(30000);
}
