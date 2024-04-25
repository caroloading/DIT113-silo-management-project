#include "CustomWiFi.h"


CustomWiFi::CustomWiFi(const char* ssid,const char* password)
{
    _ssid = ssid;
    _password = password;
}

void CustomWiFi::ConnectToWiFi()
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    
    int retries = 0;
    do {
        Serial.println("connecting to WiFi");
        WiFi.begin(_ssid, _password);
        if (retries > 0) {
            delay(5000);
        }
        retries += 1;
    } while (!IsConnected());
}

bool CustomWiFi::IsConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

String CustomWiFi::GetLocalIpAddress()
{
    return WiFi.localIP().toString();
}

void CustomWiFi::CheckConnection()
{
    if (IsConnected()) {
        return;
    }

    ConnectToWiFi();
}

