#include <DateTime.h>
#include <RTC_SAMD51.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

#include "secrets.h"

#include "ThermometerAndHumidity.h"
#include "MqttClient.h"
#include "TFT_eSPI.h"
#include "CustomWiFi.h"
#include "Ranger.h"
#include "LedBar.h"
#include "ModeButton.h"
#include "ImperialButton.h"


#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD // NOTE: Is this define necessary?
#define CHECK_BUTTONS_INTERVAL 200
#define PUBLISH_INTERVAL 15000

#define LED_BAR_CLOCK_PIN 1
#define LED_BAR_DATA_PIN 0

#define RANGER_PIN 2


TFT_eSPI tft;
RTC_SAMD51 rtc;

CustomWiFi wifi(SECRET_SSID, SECRET_PASSWORD);
MqttClient mqtt;

ThermometerAndHumidity thermometerhumidity;
LedBar ledBar(LED_BAR_CLOCK_PIN, LED_BAR_DATA_PIN, GREEN_FIRST);
Ranger ranger(RANGER_PIN);

ModeButton pauseButton(BUTTON_1);
ImperialButton imperialButton(BUTTON_2);

unsigned long lastExecutedCheckButtons = 0;
unsigned long lastExecutedPublish = 0;


void setup()
{
    rtc.begin();
    DateTime now = DateTime(F(__DATE__), F(__TIME__));
    rtc.adjust(now);

    tft.begin();
    tft.setRotation(3);
    tft.setCursor(50,100);
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(2);
    tft.fillScreen(TFT_RED);
    tft.println("connecting to wifi..");

    Serial.begin(115200);
    wifi.ConnectToWiFi();
    if(wifi.IsConnected()){
        tft.fillScreen(TFT_GREEN);
        tft.println("connected to wifi");
        tft.println("IP Adress: "+ WiFi.localIP().toString());
    }

    mqtt.Connect();
}


void loop() 
{
    unsigned long currMillis = millis();

    if (currMillis - lastExecutedCheckButtons >= CHECK_BUTTONS_INTERVAL) {
       lastExecutedCheckButtons = currMillis;
       
       pauseButton.ChangeIfPressed();
       imperialButton.ChangeIfPressed();
       Serial.println("--");
    }

    if (currMillis - lastExecutedPublish >= PUBLISH_INTERVAL) {
        lastExecutedPublish = currMillis;
        
        if (!pauseButton.IsEnabled()) {
            if (!wifi.IsConnected()) { 
                wifi.ConnectToWiFi(); 
            }
            if (!mqtt.IsConnected()) { 
                mqtt.Connect(); 
            }

            std::string distanceData = ranger.GetRangeData();
            std::string tempData = thermometerhumidity.GetTempData();
            std::string humidityData = thermometerhumidity.GetHumidityData();
            publish(distanceData.c_str(), tempData.c_str(), humidityData.c_str());
             
            displayOnTerminal(
                readValue(distanceData),
                readValue(tempData), 
                readValue(humidityData)
            );
        } else {
            displayPause();
        }
    }
}


void publish(const char* distanceData, const char* temperatureData, const char* humidityData) {
   mqtt.Publish("wio/temperature", temperatureData);
   mqtt.Publish("wio/distance", distanceData);
   mqtt.Publish("wio/humidity", humidityData);
}


void displayOnTerminal(long distance, long temperature, long humidity) {
    ledBar.UpdateDisplay(distance);
    DateTime now = rtc.now();
    tft.fillScreen(TFT_GREEN);
    tft.setCursor(10, 10);

    if(temperature < 20.0 || temperature > 35.0){
      tft.println("WARNING: Temperature out of bounds!!!");
    }
    if(humidity < 25.0 || humidity > 40.0){
      tft.println("WARNING: Humidity out of bounds!!!");
    }
    
    tft.print("Temp: ");
    if (imperialButton.IsEnabled()){
      temperature = imperialButton.ConvertToFahrenheit(temperature);
      tft.print(temperature);
      tft.println("F");
    } else {
      tft.print(temperature);
      tft.println("C");
    }
    
    tft.print("Humidity: ");
    tft.println(humidity);

    tft.print("Distance: ");
    if (imperialButton.IsEnabled()){
      distance = imperialButton.ConvertToInches(distance);
      tft.print(distance);
      tft.println(" inches");
    } else {
      tft.print(distance);
      tft.println(" cm");
    }

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


void displayPause() {
   tft.fillScreen(TFT_GREEN);
   tft.setCursor(10, 10);
   tft.println("Paused for maintenance.");
}


long readValue(std::string jsonString) {
   JsonDocument doc;
   deserializeJson(doc, jsonString);

   return doc["value"];
}
