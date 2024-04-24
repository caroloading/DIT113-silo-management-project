#ifndef mqqtClient
#define mqqtClient

#include <PubSubClient.h>
#include "rpcWiFi.h"


class MqttClient
{
  public:
    MqttClient(const char* mqtt_server = "broker.mqtt-dashboard.com",const char* clientId = "grainGuard",int serverPort = 1883);
    void Connect();
    bool IsConnected();
    void Publish(const char* topic,const char* message);

  private:
    const char* _mqtt_server;
    int         _serverPort;
    const char* _clientId;
};

#endif
