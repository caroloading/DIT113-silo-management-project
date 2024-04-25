#ifndef wioWiFi
#define wioWiFi

#include "rpcWiFi.h"
#include "WioDisplay.h"


class CustomWiFi 
{
  public:
      CustomWiFi(const char* ssid,const char* password);
      void ConnectToWiFi();
      bool IsConnected();
      String GetLocalIpAddress();
      void CheckConnection();
  private:
      const char* _ssid;
      const char* _password;
};


#endif

