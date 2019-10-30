
//Wifimanager
#include <FS.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
//mqtt and data parsing
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include <WiFiClient.h>
#include <ESP8266mDNS.h>

#include "config.h"
String inputString;
int buttonState = 0;
const int buttonPin = D0;     // the number of the pushbutton pin
//status of fryer if its running or not
//the status is determined in sensor_logic
//last status is needed so it wont spam the cloud for its update
//only send to cloud when last status is different from current status.
String lastStatus;
String currentStatus;

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


  digitalWrite(red_pin, HIGH);
  digitalWrite(green_pin, LOW);

  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
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

  //-------------------------------------------------------------------------------------------------//
  //sensor
  if (millis() - lastSensorLoopMillis > sensorLoopInterval) {
    buttonState = digitalRead(buttonPin);
    if (buttonState == 0) {
      currentStatus = "OFF";
    }
    else {
      currentStatus = "ON";
    }

    if (lastStatus != currentStatus) {
      publishData();
      lastStatus = currentStatus;
    }

    lastSensorLoopMillis = millis();
  }

  //-------------------------------------------------------------------------------------------------//

  if (millis() - lastPublishMillis > publishInterval) {

    String api = "http://10.252.153.15/input?ultrasonic=";
    HTTPClient http;
    http.begin(api);
    http.addHeader("Content-Type", "text/html");
    http.GET();
    http.end();

    lastPublishMillis = millis();
  }

  //-------------------------------------------------------------------------------------------------//



  //-------------------------------------------------------------------------------------------------//
  //Handles over the air update
  if (millis() - lastOtaMillis > otaInterval) {

    HandleOTAServer();

    lastOtaMillis = millis();
  }

  //-------------------------------------------------------------------------------------------------//

}
