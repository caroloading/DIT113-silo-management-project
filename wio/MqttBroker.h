#ifndef mqqtBroker
#define mqqtBroker

#include <PubSubClient.h>
#include "rpcWiFi.h"

class MqttBroker
{
  public:
    MqttBroker(const char* mqtt_server);
    void connect();
    void publish(const char* topic,const char* message);

  private:
    //WiFiClient wioClient;
    //PubSubClient mqttClient;
    const char* _mqtt_server;
    int _serverPort;
    const char* _clientId;

};

#endif
