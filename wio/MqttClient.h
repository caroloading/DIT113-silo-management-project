#ifndef mqqtClient
#define mqqtClient

#include <map>
#include <PubSubClient.h>
#include "rpcWiFi.h"


enum Topic
{
    HUMIDITY,
    TEMPERATURE,
    DISTANCE
};

class MqttClient
{
  public:
      MqttClient(const char* mqtt_server = "broker.mqtt-dashboard.com", const char* clientId = "grainGuard", int serverPort = 1883);
      void Connect();
      bool IsConnected();
      void Publish(Topic topic, const char* message);
      void CheckConnection();
  private:
      std::map<Topic, const char*>     _registeredTopics;
      const char*                      _mqtt_server;
      int                              _serverPort;
      const char*                      _clientId;

      void _RegisterTopic(Topic topic, const char* topicPath);
};


#endif

