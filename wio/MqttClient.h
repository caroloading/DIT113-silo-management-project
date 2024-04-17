#ifndef mqqtBroker
#define mqqtBroker

#include <PubSubClient.h>
#include "rpcWiFi.h"

class MqttBroker
{
  public:
    MqttBroker(const char* mqtt_server = "broker.mqtt-dashboard.com",const char* clientId = "grainGuard",int serverPort = 1883);
    void connect();
    void publish(const char* topic,const char* message);

  private:
    const char* _mqtt_server;
    int _serverPort;
    const char* _clientId;
};

#endif
