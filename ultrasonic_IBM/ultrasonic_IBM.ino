#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h> 
const char* ssid = "IOT";
const char* password = "3201antel";
const int sensor_pin = A0;
#define TRIGGERPIN D1
#define ECHOPIN    D2
float moisture_percentage;
#define ORG "2b9cz4"
#define DEVICE_TYPE "HC-SR04"
#define DEVICE_ID "nodemcu"
#define TOKEN "APFR_1OtrZwcKp?(-T"
bool isActivatedReading = false;
char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;
const char publishTopic[] = "iot-2/evt/sensor/fmt/json";
const char publishTopic1[] = "iot-2/evt/status/fmt/json";
const char responseTopic[] = "iotdm-1/response";
const char manageTopic[] = "iotdevice-1/mgmt/manage";
const char updateTopic[] = "iotdm-1/device/update";
const char rebootTopic[] = "iotdm-1/mgmt/initiate/device/reboot";
const char commandTopic[] = "iot-2/cmd/soil_reading_switch/fmt/json";
void callback(char* topic, byte* payload, unsigned int payloadLength);
WiFiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);
int publishInterval = 5000; // 30 seconds
long lastPublishMillis;
 long duration, distance;
void setup() {
  Serial.begin(115200);
  wifiConnect();
  mqttConnect();
  initManagedDevice();
    pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
}
void loop() {
  if (millis() - lastPublishMillis > publishInterval) {
    digitalWrite(TRIGGERPIN, LOW);
  delayMicroseconds(3);

  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(12);

  digitalWrite(TRIGGERPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.println(distance);
    publishData();
    
    lastPublishMillis = millis();
  }
  if (!client.loop()) {
    mqttConnect();
    initManagedDevice();
  }
}
