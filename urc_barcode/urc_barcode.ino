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

bool enableOTA = false;
char myIP[20];
char myMAC[25];

WiFiManager wifiManager;

void callback(char* topic, byte* payload, unsigned int payloadLength);
WiFiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);

void setup() {

  Serial.begin(9600);

  pinMode(green_pin, OUTPUT);
  pinMode(red_pin, OUTPUT);
  pinMode(button_pin, INPUT);

  digitalWrite(red_pin, HIGH);
  digitalWrite(green_pin, LOW);

  wifiConnect();
  initOTAServer();
  initBarcode();
  mqttConnect();
  initManagedDevice();
  initTime();

}

//millis for publish device status
int publishInterval = 60000;
long lastPublishMillis;

//millis for software serial reading
int swInterval = 100;
long lastSWMillis;

int otaInterval = 100;
long lastOtaMillis;

void loop() {

  //mqtt
  if (!client.loop()) {
    mqttConnect();
    initManagedDevice();

  }

  //-------------------------------------------------------------------------------------------------//
  if (millis() - lastSWMillis > swInterval) {

    HandleBarcode();

    lastSWMillis = millis();
  }


  //Handles over the air update
  if (millis() - lastOtaMillis > otaInterval) {

    HandleOTAServer();

    lastOtaMillis = millis();
  }

  //-------------------------------------------------------------------------------------------------//
}
