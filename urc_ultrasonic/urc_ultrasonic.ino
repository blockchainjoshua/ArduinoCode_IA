
//Wifimanager
#include <FS.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#define reading 0
//mqtt and data parsing
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include <WiFiClient.h>
#include <ESP8266mDNS.h>

#include "config.h"
String serialHTML;
String ipAdd;
String stat = "idle";
int stabilityCount;
String inputString;
int buttonState = 0;
long duration, currentDistance, lastDistance;

//status of fryer if its running or not
//the status is determined in sensor_logic
//last status is needed so it wont spam the cloud for its update
//only send to cloud when last status is different from current status.
bool lastStatus;
bool currentStatus;

bool showSensorReading = false;

WiFiManager wifiManager;

void callback(char* topic, byte* payload, unsigned int payloadLength);
WiFiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);

//for reset
void(* resetFunc) (void) = 0; //declare reset function @ address 0

void setup() {

  Serial.begin(9600);
  pinMode(green_pin, OUTPUT);
  pinMode(red_pin, OUTPUT);
  pinMode(button_pin, INPUT);

  digitalWrite(red_pin, HIGH);
  digitalWrite(green_pin, LOW);


  InitSensor();
  wifiConnect();
  InitOTAServer();
  mqttConnect();
  initManagedDevice();
}

//millis for publish device status
int publishInterval = 5000;
long lastPublishMillis;

int stabilityInterval = 100;
long lastStabilityMillis;

//millis for sensor reading
int sensorLoopInterval = 1000;
long lastSensorLoopMillis;

//input reading millis
int buttonInterval = 1000;
long lastButtonMillis;

//input reading millis
int otaInterval = 100;
long lastOtaMillis;


void loop() {
  //mqtt
  if (!client.loop()) {
    mqttConnect();
    initManagedDevice();

  }

  //-------------------------------------------------------------------------------------------------//
  if (millis() - lastButtonMillis > buttonInterval) {

    buttonState = digitalRead(button_pin);

    if (buttonState == HIGH)
    {
#ifdef DEBUG
      //Serial.println(buttonState);
#endif

      //reset wifi settings.
      //ResetSettings();
    }

    lastButtonMillis = millis();
  }

  //-------------------------------------------------------------------------------------------------//
  //sensor
  if (millis() - lastSensorLoopMillis > sensorLoopInterval) {

    SensorLoop();
    SerialClear();
    serialHTML += "Distance: ";
    serialHTML += (int)currentDistance;
    serialHTML += "\n";
    lastSensorLoopMillis = millis();
  }

  //-------------------------------------------------------------------------------------------------//

  if (millis() - lastPublishMillis > publishInterval) {

    String api = "http://10.252.153.15/input?ultrasonic=";
    api += stat;
    HTTPClient http;
    http.begin(api);
    http.addHeader("Content-Type", "text/html");
    http.GET();
    http.end();

    lastPublishMillis = millis();
  }

  //-------------------------------------------------------------------------------------------------//

  if (millis() - lastStabilityMillis > stabilityInterval) {

    if (stabilityCount > 10)

    {
      Serial.print(currentDistance);
      Serial.print("-");
      Serial.println(stabilityCount);

      Serial.println("IDLE MODE!!!!");
      serialHTML += "IDLE MODE!!!!";
      serialHTML += "\n";
      stat = "idle";
    }

    else {
      Serial.print(currentDistance);
      Serial.print("-");
      Serial.println(stabilityCount);
      Serial.println("Running..");
      serialHTML += "Running..!!!!";
      serialHTML += "\n";
      stat = "running";
    }

    lastStabilityMillis = millis();
  }

  //-------------------------------------------------------------------------------------------------//
  //Handles over the air update
  if (millis() - lastOtaMillis > otaInterval) {

    HandleOTAServer();

    lastOtaMillis = millis();
  }

  //-------------------------------------------------------------------------------------------------//

}
