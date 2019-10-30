/*
   Here's where we perform all cloud services
*/

//connect to mqtt broker
void mqttConnect() {
  if (!!!client.connected()) {

#ifdef DEBUG
    Serial.print("Reconnecting MQTT client to "); Serial.println(server);
    serialHTML += "Reconnecting MQTT client to ";
    serialHTML += server;
    serialHTML += "\n\n";
#endif

    while (!!!client.connect(clientId, authMethod, token)) {

#ifdef DEBUG
      Serial.print(".");
      serialHTML += ".";
#endif

      delay(500);

      if (digitalRead(red_pin) == HIGH)
      {
        digitalWrite(red_pin, LOW);
      }

      else {
        digitalWrite(red_pin, HIGH);
      }
    }

    digitalWrite(red_pin, LOW);
    digitalWrite(green_pin, HIGH);
    Serial.println();
  }
}

//initialize managed devices
void initManagedDevice() {

  client.subscribe("iotdm-1/response");
  client.subscribe("iotdm-1/device/update");
  client.subscribe(rebootTopic);
  client.subscribe(getIPTopic);

  StaticJsonBuffer<512> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  JsonObject& d = root.createNestedObject("d");
  JsonObject& metadata = d.createNestedObject("metadata");
  metadata["publishInterval"] = publishInterval;
  JsonObject& supports = d.createNestedObject("supports");
  supports["deviceActions"] = true;

  char buff[512];
  root.printTo(buff, sizeof(buff));

#ifdef DEBUG
  Serial.println("publishing device metadata:"); Serial.println(buff);
  serialHTML += "publishing device metadata:\n";
  serialHTML += buff;
  serialHTML += "\n";
#endif

  if (client.publish(manageTopic, buff)) {

#ifdef DEBUG
    Serial.println("device Publish ok");
    serialHTML += "device Publish ok\n";
#endif

  } else {

#ifdef DEBUG
    Serial.println("device Publish failed:");
    serialHTML += "device Publish failed: \n";
#endif

  }
}

void callback(char* topic, byte * payload, unsigned int payloadLength)
{

#ifdef DEBUG
  Serial.print("callback invoked for topic: "); Serial.println(topic);
  serialHTML += "callback invoked for topic: ";
  serialHTML += topic;
  serialHTML += "\n";
#endif

  if (strcmp (getIPTopic, topic) == 0)
  {
    char payload[64];
    StaticJsonBuffer<256> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["ip"] = ipToString(WiFi.localIP());
    root["mac"] = String(WiFi.macAddress());
    root.printTo(payload, 256);
    publishData(payload, publishIPTopic);
  }

  //reboot
  if (strcmp (rebootTopic, topic) == 0)
  {

#ifdef DEBUG
    Serial.println("Rebooting...");
    serialHTML += "Rebooting...";
    serialHTML += "\n";
#endif

    delay(5000);
    //initialize clamp sensor

    digitalWrite(red_pin, HIGH);
    digitalWrite(green_pin, LOW);
    InitSensor();

    wifiConnect();
    mqttConnect();
    initManagedDevice();
  }

  if (strcmp (updateTopic, topic) == 0)
  {
    handleUpdate(payload);
  }
}

void handleUpdate(byte* payload)
{
  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject((char*)payload);
  if (!root.success())
  {

#ifdef DEBUG
    Serial.println("handleUpdate: payload parse FAILED");
    serialHTML += "handleUpdate: payload parse FAILED";
    serialHTML += "\n";

#endif

    return;
  }

#ifdef DEBUG
  Serial.println("handleUpdate payload:"); root.prettyPrintTo(Serial); Serial.println();
  serialHTML += "handleUpdate payload:";
  serialHTML += "\n";
#endif


  JsonObject& d = root["d"];
  JsonArray& fields = d["fields"];
  for (JsonArray::iterator it = fields.begin(); it != fields.end(); ++it) {
    JsonObject& field = *it;
    const char* fieldName = field["field"];
    if (strcmp (fieldName, "metadata") == 0) {
      JsonObject& fieldValue = field["value"];
      if (fieldValue.containsKey("publishInterval")) {
        publishInterval = fieldValue["publishInterval"];

#ifdef DEBUG
        Serial.print("publishInterval:"); Serial.println(publishInterval);
        serialHTML += "publishInterval:";
        serialHTML += publishInterval;
        serialHTML += "\n:";
#endif

      }
    }
  }
}

void publishData(char* payload, const char* topic)
{

#ifdef DEBUG
  Serial.print("Sending payload: ");
  Serial.println(payload);
  serialHTML += "Sending payload: ";
  serialHTML += payload;
  serialHTML += "\n:";
#endif
  //you can modify the publish topic in the config.h
  if (client.publish(topic, (char*) payload))
  {

#ifdef DEBUG
    Serial.println("Publish OK");
    serialHTML += "Publish OK";
    serialHTML += "\n:";
#endif

  }

  else
  {

#ifdef DEBUG
    Serial.println("Publish FAILED");
    serialHTML += "Publish FAILED";
    serialHTML += "\n:";
#endif


  }
}
