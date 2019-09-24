#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h> 
const char* ssid = "IOT";
const char* password = "3201antel";
const int sensor_pin = A0;
float moisture_percentage;
#define ORG "2b9cz4"
#define DEVICE_TYPE "soilsensor"
#define DEVICE_ID "moisture"
#define TOKEN "nauN988FTy6kfxBHdv"
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

void setup() {
  Serial.begin(115200);
  wifiConnect();
  mqttConnect();
  initManagedDevice();
}
void loop() {
  if (millis() - lastPublishMillis > publishInterval) {
    moisture_percentage = map(moisture_percentage,750,180,0,100);
    moisture_percentage = ( 100.00 - ( (analogRead(sensor_pin) / 1023.00) * 100.00 ) );
    if(isActivatedReading == 1){
    publishData();
    }
    lastPublishMillis = millis();
  }
  if (!client.loop()) {
    mqttConnect();
    initManagedDevice();
  }
}
