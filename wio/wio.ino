#include <PubSubClient.h>
#include "rpcWiFi.h"
#include "TFT_eSPI.h"

TFT_eSPI tft;
#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD


const char* ssid= "Redmi 10C";
const char* password = "133377kolak";
const char* mqtt_server = "broker.mqtt-dashboard.com";

WiFiClient wioClient;
PubSubClient client(wioClient);


void connectWiFi(){
  tft.begin();
  tft.setRotation(3);
  tft.setCursor(50,100);
  tft.setTextColor(TFT_BLACK);          //sets the text colour to black
  tft.setTextSize(1);                   //sets the size of text
  tft.setTextSize(2);
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();    //disconnect if already connected
  tft.fillScreen(TFT_RED);
  tft.println("connecting to WiFi");
  Serial.println("connecting to WiFi");
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");

    delay(5000);
    connectWiFi();
  }
  
  tft.fillScreen(TFT_GREEN);

  tft.println("WiFi connected");
  tft.println("IP Adress: "+ WiFi.localIP().toString());
  
  Serial.println("wifi connected");
  Serial.println("IP Adress: "+ WiFi.localIP().toString());

  
}

void publish(){

  
while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "viktorWIO";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
     
    }
    
}

client.publish("wio/information", "23C");
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  connectWiFi();

  client.setServer(mqtt_server, 1883); // Connect the MQTT Server
 
}

void loop() {
while(WiFi.status() != WL_CONNECTED){
  connectWiFi();
}

publish();
delay(30000);
}
