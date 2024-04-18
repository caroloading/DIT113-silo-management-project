#include "MqttClient.h"
#include "TFT_eSPI.h"
#include "secrets.h"
#include "CustomWiFi.h"
#include "Ranger.h"
#include "LedBar.h"
#include "ModeButton.h"

#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD

TFT_eSPI tft;
CustomWiFi wifi(ssid, password);
MqttClient mqtt;
LedBar ledBar(1, 0, GREEN_FIRST);
Ranger ranger(2);
ModeButton pauseButton(BUTTON_1);

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
  if(wifi.isConnected()){
    tft.fillScreen(TFT_GREEN);
    tft.println("connected to wifi");
    tft.println("IP Adress: "+ WiFi.localIP().toString());
  }
  mqtt.connect(); // Connect the MQTT Server
    
 
}

void loop() {
  if (!pauseButton.isEnabled()){
    while(!wifi.isConnected()){
      tft.println("connecting to wifi");
      wifi.connectToWiFi();
    }
    long distance = ranger.MeasureRange();
    
    mqtt.publish("wio/temperature","23.01/2024-04-17 09:23:21");//publishes to the broker
    mqtt.publish("wio/distance", "24.56/2024-04-17 09:23:21");
    mqtt.publish("wio/humidity","58.00/2024-04-17 09:24:22");

    displayOnTerminal(distance, 0, 0);
  } else {
    Serial.println("Paused for maintenance.");
  }
  
  pauseButton.ChangeIfPressed();

  delay(15000);
}

void publish(char* distance, char* temperature, char* humidity){
  //TO-DO: PUBLISH JSON STRINGS
}

void displayOnTerminal(long distance, long temperature, long humidity){
  ledBar.UpdateDisplay(distance);
  tft.print("Distance: ");
  tft.println(distance);
  tft.print("Temp: ");
  tft.print(temperature);
  tft.println("°C");
  tft.print("Humidity: ");
  tft.println(humidity);
}
