#include "WioDisplay.h"

/* LCD pixel coordinates */
int32_t temp_label_xpos = 80, temp_label_ypos = 100;
int32_t temp_value_xpos = 80, temp_value_ypos = 50;
int32_t rh_label_xpos = 80, rh_label_ypos = 200;
int32_t rh_value_xpos = 80, rh_value_ypos = 150;
int32_t gh_label_xpos = 240, gh_label_ypos = 170;
int32_t gh_value_xpos = 240, gh_value_ypos = 120;
int32_t brect_xpos = 0, brect_ypos = 220, brect_width = 320, brect_height = 20; 
int32_t btext_xpos = 160, btext_ypos = 230; 
int32_t mid_width = 160, mid_height = 120;

/* save current data when switching between units with the  mode button */
double prevDisplayedTemp = 0, prevDisplayedDist = 0; 
double WioDisplay::savedTemperature = 0, WioDisplay::savedHumidity = 0, WioDisplay::savedDistance = 0;

WioDisplay::WioDisplay() { }

void WioDisplay::DisplayBackground() 
{
    const uint8_t LANDSCAPE = 3;

    tft.setRotation(LANDSCAPE);
    tft.fillScreen(TFT_BLACK);
    tft.setTextDatum(TC_DATUM); // TC = top center text alignment
}

void WioDisplay::DisplayLines() 
{
    int32_t hline_xpos = 10, hline_ypos = 130, width = 140;
    int32_t vline_xpos = 160, vline_ypos = 50, height = 170;
  
    tft.drawFastHLine(hline_xpos, hline_ypos, width, TFT_WHITE);
    tft.drawFastVLine(vline_xpos, vline_ypos, height, TFT_WHITE);
}

void WioDisplay::DisplayLabels() 
{
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE, TFT_BLACK); 
    tft.drawString(F("Temp (C)"), temp_label_xpos, temp_label_ypos); // F(string_literal) macro: returns const string 
    tft.drawString(F("R.H. (%)"), rh_label_xpos, rh_label_ypos);
    tft.drawString(F("G. Lvl (cm)"), gh_label_xpos, gh_label_ypos);
}

void WioDisplay::DisplayWifiStatus(bool isConnected) 
{
    int32_t xpos = 30, ypos = 10;
    const char* WIFI_STATUS_LABEL = "WiFi";
 
    tft.setTextSize(2);
    if (isConnected) {
        tft.setTextColor(TFT_GREEN, TFT_BLACK);  
        tft.drawString(WIFI_STATUS_LABEL, xpos, ypos);
    } else {
        tft.setTextColor(TFT_RED, TFT_BLACK);  
        tft.drawString(WIFI_STATUS_LABEL, xpos, ypos);
    }
}

void WioDisplay::DisplayMqttStatus(bool isConnected) 
{
    int32_t xpos = 290, ypos = 10;
    const char* MQTT_STATUS_LABEL = "MQTT";

    tft.setTextSize(2);
    if (isConnected) {
        tft.setTextColor(TFT_GREEN, TFT_BLACK);  
        tft.drawString(MQTT_STATUS_LABEL, xpos, ypos);
    } else {
        tft.setTextColor(TFT_RED, TFT_BLACK);  
        tft.drawString(MQTT_STATUS_LABEL, xpos, ypos);
    }
}

void WioDisplay::DisplayPause(const char* msg)
{
    tft.setTextSize(2);
    tft.fillRect(brect_xpos, brect_ypos, brect_width, brect_height, TFT_YELLOW);
    tft.setTextColor(TFT_BLACK);
    tft.drawString(msg, btext_xpos, btext_ypos);
}

void WioDisplay::DisplayWarning(const char* text)
{
    char* warningBuffer = new char[100];
    std::sprintf(warningBuffer, "%s!", text);
 
    tft.setTextSize(2);
    tft.fillRect(brect_xpos, brect_ypos, brect_width, brect_height, TFT_RED);
    tft.setTextColor(TFT_BLACK);
    tft.drawString(warningBuffer, btext_xpos, btext_ypos);
}

void WioDisplay::HideWarning()
{
    tft.fillRect(brect_xpos, brect_ypos, brect_width, brect_height, TFT_BLACK);
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
    int32_t xpos = 160, ypos = 10; 
    char dateBuffer[16];

    sprintf(dateBuffer,"%04u-%02u-%02u %02u:%02u",
                        now.year(),now.month(),now.day(), 
                        now.hour(),now.minute());
                        
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString(dateBuffer, xpos, ypos);
}

void WioDisplay::DisplayMeasurement(const char* label, const char* m_unit, double measurement)
{
    char* labelBuffer = new char[100];
    std::sprintf(labelBuffer, "%s (%s)", label, m_unit);
    String measureToDisplay = String(measurement, 2);
    String strLabel = String(label);
    String strMUnit = String(m_unit); 
    
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    if (strLabel == "Temp") {
        tft.setTextSize(2);
        tft.drawString(labelBuffer, temp_label_xpos, temp_label_ypos);
        tft.setTextSize(4);
        tft.setTextColor(TFT_BLACK);
        tft.drawString(String(prevDisplayedTemp), temp_value_xpos, temp_value_ypos);
        tft.setTextColor(TFT_WHITE);
        tft.drawString(measureToDisplay, temp_value_xpos, temp_value_ypos);
        if (strMUnit == "C") { savedTemperature = measurement; }
        prevDisplayedTemp = measurement; 
    } else if (strLabel == "R.H.") {
        tft.setTextSize(2);
        tft.drawString(labelBuffer, rh_label_xpos, rh_label_ypos);
        tft.setTextSize(4);
        tft.setTextColor(TFT_BLACK);
        tft.drawString(String(savedHumidity), rh_value_xpos, rh_value_ypos);
        tft.setTextColor(TFT_WHITE);
        tft.drawString(measureToDisplay, rh_value_xpos, rh_value_ypos);
        savedHumidity = measurement; 
    } else if (strLabel == "G. Lvl") {
        tft.setTextSize(2); 
        tft.drawString(labelBuffer, gh_label_xpos, gh_label_ypos);
        tft.setTextSize(4);
        tft.setTextColor(TFT_BLACK);
        tft.drawString(String(prevDisplayedDist), gh_value_xpos, gh_value_ypos);
        tft.setTextColor(TFT_WHITE);
        tft.drawString(measureToDisplay, gh_value_xpos, gh_value_ypos);
        if (strMUnit == "cm") { savedDistance = measurement; }
        prevDisplayedDist = measurement; 
    }
}
