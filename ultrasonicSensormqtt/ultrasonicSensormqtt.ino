#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
#define LED 2
 
//Enter your wifi credentials
const char* ssid = "IOT";  
const char* password =  "antel3201";
 
//Enter your mqtt server configurations
const char* mqttServer = "soldier.cloudmqtt.com";    //Enter Your mqttServer address
const int mqttPort = 16127;       //Port number
const char* mqttUser = "qtjcdwev"; //User
const char* mqttPassword = "Tu1Zq_RRFy1z"; //Password
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
  delay(1000);
  pinMode(2,OUTPUT);
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.print("Connected to WiFi :");
  Serial.println(WiFi.SSID());
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(MQTTcallback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.println(client.state());  //If you get state 5: mismatch in configuration
      delay(2000);
 
    }
  }
 
  client.publish("esp/test", "Hello from ESP8266");
  client.subscribe("esp/test");
 
}
 
void MQTTcallback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("LED Status: ");
 
  String message;
  for (int i = 0; i < length; i++) {
    message = message + (char)payload[i];  //Conver *byte to String
  }
   Serial.print(message);
  if(message == "on") {digitalWrite(2,LOW);
  client.publish("esp/test", "ON");
  client.subscribe("esp/test");}   //LED on  
  
  if(message == "off") {digitalWrite(2,HIGH);
  client.publish("esp/test", "OFF");
  client.subscribe("esp/test");} //LED off
 
 
  Serial.println();
  Serial.println("-----------------------");  
}
 
void loop() {
  client.loop();
}
