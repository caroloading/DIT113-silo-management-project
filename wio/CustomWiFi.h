#ifndef wioWiFi
#define wioWiFi


#include "rpcWiFi.h"


class CustomWiFi
{
    public:
       CustomWiFi(const char* ssid,const char* password);
       void connectToWiFi();
       bool getWiFiStatus();
    private:
      const char* _ssid;
      const char* _password;

};

#endif
