#include "MqttClient.h"


WiFiClient wioClient;
PubSubClient mqttClient(wioClient); 

MqttClient::MqttClient(const char* mqtt_server, const char* clientId, int serverPort)
{
    _registeredTopics = std::map<Topic, const char*>();
    _mqtt_server = mqtt_server;
    _clientId = clientId;
    _serverPort = serverPort;

    _RegisterTopic(Topic::HUMIDITY, "wio/humidity");
    _RegisterTopic(Topic::TEMPERATURE, "wio/temperature");
    _RegisterTopic(Topic::DISTANCE, "wio/distance");
}

void MqttClient::Connect()
{
    mqttClient.setServer(_mqtt_server, _serverPort);

    while (!IsConnected()) {
        Serial.println("Attempting MQTT connection...");
        if (mqttClient.connect(_clientId)) {
            Serial.println("connected to mqtt server");
            return;
        }
        delay(5000);
    }

    Serial.println("failed to connect to mqtt");
}

void MqttClient::Publish(Topic topic, const char* message)
{
    mqttClient.publish(_registeredTopics[topic], message);
}

bool MqttClient::IsConnected() 
{
    return mqttClient.connected();
}

void MqttClient::CheckConnection()
{
    if (IsConnected()) {
        return;
    }

    Connect();
}

void MqttClient::_RegisterTopic(Topic topic, const char* topicPath)
{
    // NOTE: this will overwrite the topic in the map if it already exists
    _registeredTopics[topic] = topicPath;
}
