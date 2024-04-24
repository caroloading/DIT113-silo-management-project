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
  
  Serial.println("connecting to WiFi");
  WiFi.begin(_ssid, _password);

  while(!IsConnected()){
    delay(5000);
    Serial.println("connecting to WiFi");
    WiFi.begin(_ssid, _password);
  }

  Serial.println("wifi connected");
  Serial.println("IP Adress: "+ WiFi.localIP().toString());
}

bool CustomWiFi::IsConnected()
{
  return WiFi.status() == WL_CONNECTED;
}
