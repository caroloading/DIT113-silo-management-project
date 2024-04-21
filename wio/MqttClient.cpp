#include "MqttClient.h"

WiFiClient wioClient;
PubSubClient mqttClient(wioClient); 

MqttClient::MqttClient(const char* mqtt_server,const char* clientId, int serverPort ){
  _mqtt_server = mqtt_server;
  _clientId = clientId;
  _serverPort = serverPort;
}

void MqttClient::connect(){
  mqttClient.setServer(_mqtt_server,_serverPort);
  while (!mqttClient.connected()) {
      Serial.println("Attempting MQTT connection...");
      if (mqttClient.connect(_clientId)) {
        Serial.println("connected to mqtt server");
        return;
      }
      delay(5000);
  }
  Serial.println("failed to connect to mqtt");
  return;
}

void MqttClient::publish(const char* topic,const char* message){
  mqttClient.publish(topic, message);
}

bool MqttClient::isConnected() {
  return mqttClient.connected();
}
