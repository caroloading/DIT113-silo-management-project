#include "WioDisplay.h"
#include <cstdio>


WioDisplay::WioDisplay() { }

void WioDisplay::DisplayPause(const char* msg)
{
    SetDefaultPreset();
    tft.println(msg);
}

void WioDisplay::DisplayConnectingToWiFi(const char* msg)
{
    tft.setRotation(3);
    tft.setCursor(50,100);
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(2);
    tft.fillScreen(TFT_RED);
    tft.println(msg);
}

void WioDisplay::DisplayConnectedToWiFi(String ipAddress)
{
    tft.fillScreen(TFT_GREEN);
    tft.println("Connected to WiFi");
    tft.println("IP Adress: " + ipAddress);
}

void WioDisplay::DisplayCurrentTime(DateTime now)
{
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

void WioDisplay::SetDefaultPreset()
{
    tft.fillScreen(TFT_GREEN);
    tft.setCursor(10, 10);
}

void WioDisplay::DisplayWarning(const char* text)
{
    char* warningBuffer = new char[100];
    std::sprintf(warningBuffer, "WARNING: %s!!!", text);
    tft.println(warningBuffer);
}

void WioDisplay::DisplayMeasurement(const char* preValue, const char* postValue, long measurement)
{
    char* measurementBuffer = new char[100];
    std::sprintf(measurementBuffer, "%s: %ld%s", preValue, measurement, postValue);
    tft.println(measurementBuffer);
}
