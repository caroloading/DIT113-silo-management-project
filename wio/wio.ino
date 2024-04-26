#include <DateTime.h>
#include <RTC_SAMD51.h>
#include <ArduinoJson.h>

#include "secrets.h"

#include "ThermometerAndHumidity.h"
#include "MqttClient.h"
#include "CustomWiFi.h"
#include "Ranger.h"
#include "LedBar.h"
#include "ModeButton.h"
#include "ImperialButton.h"
#include "SensorManager.h"
#include "RealTimeClock.h"
#include "IntervalController.h"
#include "WioDisplay.h"
#include "TFT_eSPI.h"


#define LED_BAR_CLOCK_PIN 1
#define LED_BAR_DATA_PIN 0

#define RANGER_PIN 4
#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD


TFT_eSPI tft;

RealTimeClock realTimeClock;
 
CustomWiFi wifi(SECRET_SSID, SECRET_PASSWORD);
MqttClient mqtt;
WioDisplay wioDisplay;

ThermometerAndHumidity thermometerhumidity;
LedBar ledBar(LED_BAR_CLOCK_PIN, LED_BAR_DATA_PIN, GREEN_FIRST);
Ranger ranger(RANGER_PIN);
 
ModeButton pauseButton(BUTTON_1);
ImperialButton imperialButton(BUTTON_2);
 
SensorManager sensorManager(
    &ranger,
    &ledBar,
    &pauseButton,
    &imperialButton,
    &thermometerhumidity
);

CheckButtonInterval checkButtonInterval(&imperialButton, &pauseButton);
PublishInterval publishInterval(
    &pauseButton,
    &wifi,
    &mqtt,
    &sensorManager,
    &wioDisplay,
    &realTimeClock
);
IntervalController intervalController;


void setup()
{
    Serial.begin(115200);
    tft.begin();

    wioDisplay.DisplayConnectingToWiFi();
    wifi.ConnectToWiFi();
    wioDisplay.DisplayConnectedToWiFi(wifi.GetLocalIpAddress());

    mqtt.Connect();
    
    // Register intervals that are meant to run during the loop
    intervalController.AddInterval(&checkButtonInterval);
    intervalController.AddInterval(&publishInterval);
}


void loop() 
{
    intervalController.RunIntervals(millis());
}

