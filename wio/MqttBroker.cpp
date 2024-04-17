#include "MqttBroker.h"

WiFiClient wioClient;
PubSubClient mqttClient(wioClient); 

MqttBroker::MqttBroker(const char* mqtt_server){
_mqtt_server = mqtt_server;
_clientId = "grainGuard";
_serverPort = 1883;




}

void MqttBroker::connect(){
mqttClient.setServer(_mqtt_server,_serverPort);
while (!mqttClient.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (mqttClient.connect(_clientId)) {
      Serial.print("connected to mqtt server");
      return;
     }
    delay(5000);
  }
  Serial.print("failed to connect to mqtt");
  return;
}

void MqttBroker::publish(const char* topic,const char* message){
 if (!mqttClient.connected()) {
    Serial.println("Not connected to MQTT, cannot publish");
    return;
  }
  mqttClient.publish(topic, message);

}
