#include <DateTime.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <RTC_SAMD51.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "secrets.h"

#include "ThermometerAndHumidity.h"
#include "MqttClient.h"
#include "TFT_eSPI.h"
#include "CustomWiFi.h"
#include "Ranger.h"
#include "LedBar.h"
#include "ModeButton.h"
#include "ImperialButton.h"

TFT_eSPI tft;
RTC_SAMD51 rtc;

#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD
#define CHECK_BUTTONS_INTERVAL 200
#define PUBLISH_INTERVAL 15000
#define NTP_UPDATE_INTERVAL 3600000
#define UTC_OFFSET 7200 //UTC+2 
#define NTP_SERVER "europe.pool.ntp.org"


CustomWiFi wifi(SECRET_SSID, SECRET_PASSWORD);
MqttClient mqtt;
ThermometerAndHumidity thermometerhumidity;
LedBar ledBar(1, 0, GREEN_FIRST);
Ranger ranger(2);
ModeButton pauseButton(BUTTON_1);
ImperialButton imperialButton(BUTTON_2);

DateTime now; // Datetime object
WiFiUDP ntpUDP; // UDP object 
NTPClient ntpClient(ntpUDP, NTP_SERVER, UTC_OFFSET, NTP_UPDATE_INTERVAL); // NTP object 

unsigned long lastExecutedCheckButtons = 0;
unsigned long lastExecutedPublish = 0;
unsigned long lastReceivedNTPUpdate = 0;
unsigned long devicetime; // RTC localtime (Epoch)

void setup() {

  Serial.begin(115200);
  rtc.begin();          // intialize RTC 
  ntpClient.begin();    // initialize NTPClient
  
  tft.begin();
  tft.setRotation(3);
  tft.setCursor(50,100);
  tft.setTextColor(TFT_BLACK);          //sets the text colour to black
  tft.setTextSize(2);
  tft.fillScreen(TFT_RED);
  tft.println("connecting to wifi..");

  wifi.connectToWiFi();
  if(wifi.isConnected()){
    tft.fillScreen(TFT_GREEN);
    tft.println("connected to wifi");
    tft.println("IP Adress: "+ WiFi.localIP().toString());
  }

  updateRTCUsingNTP();  // update RTC localtime

  mqtt.connect(); // Connect the MQTT Server
}


void loop() {

unsigned long currMillis = millis();

  if (currMillis - lastExecutedCheckButtons >= CHECK_BUTTONS_INTERVAL){
    lastExecutedCheckButtons = currMillis;
    
    pauseButton.ChangeIfPressed();
    imperialButton.ChangeIfPressed();
    Serial.println("--");
  }

  if (currMillis - lastExecutedPublish >= PUBLISH_INTERVAL){
    lastExecutedPublish = currMillis;
    
    if (!pauseButton.isEnabled()){

      if (!wifi.isConnected()){ wifi.connectToWiFi(); }
      if (!mqtt.isConnected()){ mqtt.connect(); }

      std::string distanceData = ranger.getRangeData();
      std::string tempData = thermometerhumidity.getTempData();
      std::string humidityData = thermometerhumidity.getHumidityData();
      publish(distanceData.c_str(), tempData.c_str(), humidityData.c_str());
  
      displayOnTerminal(readValue(distanceData), readValue(tempData), readValue(humidityData));
    } else {
      displayPause();
    }
  }

  if (currMillis - lastReceivedNTPUpdate >= NTP_UPDATE_INTERVAL){
    lastReceivedNTPUpdate = currMillis;
      
    updateRTCUsingNTP(); // update RTC localtime
  }
}

void publish(const char* distanceData, const char* temperatureData, const char* humidityData){
  mqtt.publish("wio/temperature", temperatureData);//publishes to the broker
  mqtt.publish("wio/distance", distanceData);
  mqtt.publish("wio/humidity", humidityData);
}

void displayOnTerminal(long distance, long temperature, long humidity){
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
  if (imperialButton.isEnabled()){
    temperature = imperialButton.convertToFahrenheit(temperature);
    tft.print(temperature);
    tft.println("F");
  } else {
    tft.print(temperature);
    tft.println("C");
  }
  
  tft.print("Humidity: ");
  tft.println(humidity);

  tft.print("Distance: ");
  if (imperialButton.isEnabled()){
    distance = imperialButton.convertToInches(distance);
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

void displayPause(){
  tft.fillScreen(TFT_GREEN);
  tft.setCursor(10, 10);
  tft.println("Paused for maintenance.");
}

long readValue(std::string jsonString){
  JsonDocument doc;
  deserializeJson(doc, jsonString);
  return doc["value"];
}

void updateRTCUsingNTP() {
  ntpClient.update(); // get update from NTP server 

  // get the Epoch time, i.e., time in seconds since Jan. 1, 1970
  devicetime = ntpClient.getEpochTime();
  if (devicetime == 0) {
    Serial.println("Failed to get time from network time server.");
  } 
  else {
    // adjust RTC localtime
    Serial.println("Adjust dateTime!");
    rtc.adjust(DateTime(devicetime));

    // get and log the current RTC dateTime
    now = rtc.now();
    Serial.print("RTC time is: ");
    Serial.println(now.timestamp(DateTime::TIMESTAMP_FULL)); // ISO_LOCAL_DATE_TIME
  } 
}
