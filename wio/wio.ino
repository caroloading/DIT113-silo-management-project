#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include "MqttClient.h"
#include "TFT_eSPI.h"
#include "secrets.h"
#include "CustomWiFi.h"
#include "Ranger.h"
#include "LedBar.h"
#include "ModeButton.h"

#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD
#define CHECK_BUTTONS_INTERVAL 200
#define PUBLISH_INTERVAL 15000

TFT_eSPI tft;
CustomWiFi wifi(ssid, password);
MqttClient mqtt;
LedBar ledBar(1, 0, GREEN_FIRST);
Ranger ranger(2);
ModeButton pauseButton(BUTTON_1);

unsigned long lastExecutedCheckButtons = 0;
unsigned long lastExecutedPublish = 0;

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
  unsigned long currMillis = millis();

  if (currMillis - lastExecutedCheckButtons >= CHECK_BUTTONS_INTERVAL){
    lastExecutedCheckButtons = currMillis;
    
    pauseButton.ChangeIfPressed();
  }
  
  if (currMillis - lastExecutedPublish >= PUBLISH_INTERVAL){
    lastExecutedPublish = currMillis;
    
    if (!pauseButton.isEnabled()){

      if (!wifi.isConnected()){ wifi.connectToWiFi(); }
      if (!mqtt.isConnected()){ mqtt.connect(); }

      std::string distanceData = ranger.getRangeData();
      std::string tempData = "{\"value\": 23.01}";
      std::string humidityData = "{\"value\": 56.01}";
      publish(distanceData.c_str(), tempData.c_str(), humidityData.c_str());
  
      displayOnTerminal(readValue(distanceData), 0, 0);
    }
  }
}

void publish(const char* distanceData, const char* temperatureData, const char* humidityData){
  mqtt.publish("wio/temperature", temperatureData);//publishes to the broker
  mqtt.publish("wio/distance", distanceData);
  mqtt.publish("wio/humidity", humidityData);
}

void displayOnTerminal(long distance, long temperature, long humidity){
  ledBar.UpdateDisplay(distance);
  tft.fillScreen(TFT_GREEN);
  tft.setCursor(10, 10);
  tft.print("Distance: ");
  tft.println(distance);
  tft.print("Temp: ");
  tft.print(temperature);
  tft.println("C");
  tft.print("Humidity: ");
  tft.println(humidity);
}

long readValue(std::string jsonString){
  JsonDocument doc;
  deserializeJson(doc, jsonString);
  return doc["value"];
}
