#include "MqttClient.h"


WiFiClient wioClient;
PubSubClient mqttClient(wioClient); 

MqttClient::MqttClient(const char* mqtt_server, const char* clientId, int serverPort)
{
    _registeredTopics = {
        {Topic::HUMIDITY, "wio/humidity"},
        {Topic::TEMPERATURE, "wio/temperature"},
        {Topic::DISTANCE, "wio/distance"}
    };

    _mqtt_server = mqtt_server;
    _clientId = clientId;
    _serverPort = serverPort;
}

// TODO: this could be re-written to avoid early returns
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

