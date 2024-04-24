#ifndef wioWiFi
#define wioWiFi

#include "rpcWiFi.h"


class CustomWiFi 
{
  public:
      CustomWiFi(const char* ssid,const char* password);
      void ConnectToWiFi();
      bool IsConnected();
  private:
      const char* _ssid;
      const char* _password;
};


#endif

