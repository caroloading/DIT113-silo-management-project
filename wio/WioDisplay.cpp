#include "WioDisplay.h"
#include <cstdio>


WioDisplay::WioDisplay() : _tft() 
{
    _tft.begin();
}

void WioDisplay::DisplayPause(const char* msg)
{
    SetDefaultPreset();
    _tft.println(msg);
}

void WioDisplay::DisplayConnectingToWiFi(const char* msg)
{
    _tft.setRotation(3);
    _tft.setCursor(50,100);
    _tft.setTextColor(TFT_BLACK);
    _tft.setTextSize(2);
    _tft.fillScreen(TFT_RED);
    _tft.println(msg);
}

void WioDisplay::DisplayConnectedToWiFi(String ipAddress)
{
    _tft.fillScreen(TFT_GREEN);
    _tft.println("Connected to WiFi");
    _tft.println("IP Adress: " + ipAddress);
}

void WioDisplay::DisplayCurrentTime(DateTime now)
{
    _tft.print(" Date: ");
    _tft.print(now.year(), DEC);
    _tft.print('/');
    _tft.print(now.month(), DEC);
    _tft.print('/');
    _tft.print(now.day(), DEC);
    _tft.print("   ");
    _tft.print(now.hour(), DEC);
    _tft.print(':');
    _tft.print(now.minute(), DEC);
    _tft.println();
}

void WioDisplay::SetDefaultPreset()
{
    _tft.fillScreen(TFT_GREEN);
    _tft.setCursor(10, 10);
}

void WioDisplay::DisplayWarning(const char* text)
{
    char* warningBuffer = new char[100];
    std::sprintf(warningBuffer, "WARNING: %s!!!", text);
    _tft.println(warningBuffer);
}

void WioDisplay::DisplayMeasurement(const char* preValue, const char* postValue, long measurement)
{
    char* measurementBuffer = new char[100];
    std::sprintf(measurementBuffer, "%s: %ld %s", preValue, measurement, postValue);
    _tft.println(measurementBuffer);
}
