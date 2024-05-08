#include <DateTime.h>
#include <RTC_SAMD51.h>

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


#define NTP_UPDATE_INTERVAL 3600000
#define UTC_OFFSET 7200 // UTC+2
#define NTP_SERVER "europe.pool.ntp.org"

#define LED_BAR_CLOCK_PIN 1
#define LED_BAR_DATA_PIN 0

#define RANGER_PIN 4
#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD


TFT_eSPI tft;

WiFiUDP ntpUDP; // UDP object 
NTPClient ntpClient(ntpUDP, NTP_SERVER, UTC_OFFSET, NTP_UPDATE_INTERVAL); // NTP object 

RealTimeClock realTimeClock(NTP_UPDATE_INTERVAL);
 
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
    &thermometerhumidity,
    &realTimeClock
);

CheckButtonInterval checkButtonInterval(&imperialButton, &pauseButton, &wioDisplay, &sensorManager);
PublishInterval publishInterval(
    &pauseButton,
    &wifi,
    &mqtt,
    &sensorManager,
    &wioDisplay,
    &realTimeClock
);
NtpUpdateInterval ntpUpdateInterval(&realTimeClock);
DisplayInterval displayInterval(
    &wifi,
    &mqtt,
    &wioDisplay,
    &realTimeClock
);
IntervalController intervalController;


void setup()
{
    Serial.begin(115200);
    tft.begin();
    ntpClient.begin();

    wioDisplay.DisplayConnectingToWiFi();
    wifi.ConnectToWiFi();
    wioDisplay.DisplayConnectedToWiFi(wifi.GetLocalIpAddress());

    realTimeClock.UpdateRtcUsingNtp();

    mqtt.Connect();
    
    // Register intervals that are meant to run during the loop
    intervalController.AddInterval(&checkButtonInterval);
    intervalController.AddInterval(&publishInterval);
    intervalController.AddInterval(&ntpUpdateInterval);
    intervalController.AddInterval(&displayInterval);

    delay(1000); // pause 

    // display simple dashboard 
    wioDisplay.DisplayBackground();
    wioDisplay.DisplayLines();
    wioDisplay.DisplayLabels();
    wioDisplay.DisplayWifiStatus(wifi.IsConnected());
    wioDisplay.DisplayCurrentTime(realTimeClock.GetNow());
    wioDisplay.DisplayMqttStatus(mqtt.IsConnected()); 

    // initial publish 
    sensorManager.PublishAndUpdateSensorMeasurements(&mqtt, &wioDisplay);
}


void loop() 
{
    intervalController.RunIntervals(millis());
}

