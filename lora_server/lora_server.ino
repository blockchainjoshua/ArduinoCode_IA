#include <FS.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <RHReliableDatagram.h>
#include <RH_RF95.h>
#include <SPI.h>
#include <Wire.h>
#include "config.h"

WiFiManager wifiManager;

void callback(char* topic, byte* payload, unsigned int payloadLength);

WiFiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);


int publishInterval = 1000;
long lastPublishMillis;

int loraInterval = 1000;
long lastLoraMillis;

void setup()
{
  Serial.begin(9600);

  pinMode(INDICATOR, OUTPUT);
  
  LoraInit();
 // wifiConnect();
  //mqttConnect();
 // initManagedDevice();
}

void loop()
{

  //mqtt
//  if (!client.loop()) {
//    mqttConnect();
//    initManagedDevice();
//    digitalWrite(INDICATOR, HIGH);
//  }
//
//  else{
//    digitalWrite(INDICATOR, LOW);
//  }

  //publish temperature
  if (millis() - lastPublishMillis > publishInterval) {
    //publishData();
    lastPublishMillis = millis();
  }

  //publish lora reading
  if (millis() - lastLoraMillis > loraInterval) {
    LoraSend("Recieving message from 433 frequency",CLIENT_ADDRESS_RELAYS);
    //LoraServer();
    //LoraBroadcast();
    
    lastLoraMillis = millis();
  }
}
