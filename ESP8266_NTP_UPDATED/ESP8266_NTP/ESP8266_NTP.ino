/*
 * Office Automation Scheduling
 * 
 * Author: Joshua Malabanan
 */
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define ORG "2b9cz4"
#define DEVICE_TYPE "ntp"
#define DEVICE_ID "alarm"
#define TOKEN "0CxjIQ*iAT0t_j(uO2"
bool relay1Status = false;
bool relay2Status = false;
char  json1[512];
char  prev_json1[512];
char  json2[512];
char  prev_json2[512];
char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;
const char publishTopic[] = "iot-2/evt/status/fmt/json";
const char responseTopic[] = "iotdm-1/response";
const char manageTopic[] = "iotdevice-1/mgmt/manage";
const char updateTopic[] = "iotdm-1/device/update";
const char rebootTopic[] = "iotdm-1/mgmt/initiate/device/reboot";
const char commandTopic[] = "iot-2/cmd/schedcommand/fmt/json";
const char commandTopic2[] = "iot-2/cmd/schedcommand2/fmt/json";
void callback(char* topic, byte* payload, unsigned int payloadLength);
WiFiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);
int publishInterval = 1000; // 30 seconds
long lastPublishMillis;
int sched_interval1 = 1000;
long lastSchedMillis1;
String input;
long int timeNow = 0;
long int timer = 0;
const char *ssid     = "IOT";
const char *password = "3201antel";
const long utcOffsetInSeconds = 28800;
char daysOfTheWeek[7][12] = {"SUN", "M", "T", "W", "TTH", "F", "SAT"};
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "time.upd.edu.ph", utcOffsetInSeconds);
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  wifiConnect();
  mqttConnect();
  initManagedDevice();
  timeClient.begin();
}
  void loop() {

  if (millis() - lastSchedMillis1 > sched_interval1)
  {
    TimeChecker(json1);
    TimeChecker(json2);
    
    RelayStatusChecker();
    lastSchedMillis1 = millis();
  }
  if (millis() - lastPublishMillis > publishInterval) {
    ScheduleLoop();
    lastPublishMillis = millis();
  }
  if (!client.loop()) {
    mqttConnect();
    initManagedDevice();
  }
}
