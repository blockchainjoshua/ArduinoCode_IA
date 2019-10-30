/*
   Connecting to internet

   Author: Joshua Malabanan
*/

void wifiConnect() {
  Serial.print("Connecting to "); Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {    // Loop until we're reconnected
    delay(500);
    Serial.print(".");
  }
  Serial.print("WiFi connected, IP address: "); Serial.println(WiFi.localIP());
}
/*
   Connecting to IBM CLOUD
*/
void mqttConnect() {
  if (!!!client.connected()) {
    Serial.print("Reconnecting MQTT client to "); Serial.println(server);
    while (!!!client.connect(clientId, authMethod, token)) {
      Serial.print(".");
      delay(500);
    }
    Serial.println();
  }
}
/*
   Initialize the topics
*/
void initManagedDevice() {
  if (client.subscribe("iotdm-1/response")) {
    Serial.println("subscribe to responses OK");
  } else {
    Serial.println("subscribe to responses FAILED");
  }

  if (client.subscribe(rebootTopic)) {
    Serial.println("subscribe to reboot OK");
  } else {
    Serial.println("subscribe to reboot FAILED");
  }
  if (client.subscribe(commandTopic)) {
    Serial.println("subscribe to command1 OK");
  } else {
    Serial.println("subscribe to command1 FAILED");
  }
  if (client.subscribe(commandTopic2)) {
    Serial.println("subscribe to command2 OK");
  } else {
    Serial.println("subscribe to command2 FAILED");
  }
  if (client.subscribe(commandTopic3)) {
    Serial.println("subscribe to command3 OK");
  } else {
    Serial.println("subscribe to command3 FAILED");
  }
  if (client.subscribe(commandTopic4)) {
    Serial.println("subscribe to command4 OK");
  } else {
    Serial.println("subscribe to command4 FAILED");
  }

  if (client.subscribe("iotdm-1/device/update")) {
    Serial.println("subscribe to update OK");
  } else {
    Serial.println("subscribe to update FAILED");
  }
  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  JsonObject& d = root.createNestedObject("d");
  JsonObject& metadata = d.createNestedObject("metadata");
  metadata["publishInterval"] = publishInterval;
  JsonObject& supports = d.createNestedObject("supports");
  supports["deviceActions"] = true;

  char buff[300];
  root.printTo(buff, sizeof(buff));
  Serial.println("publishing device metadata:"); Serial.println(buff);
  if (client.publish(manageTopic, buff)) {
    Serial.println("device Publish ok");
  } else {
    Serial.print("device Publish failed:");
  }
}
void publishData() {
}
void callback(char* topic, byte* payload, unsigned int payloadLength) {
  Serial.print("callback invoked for topic: "); Serial.println(topic);
  //
  //
  if (strcmp (responseTopic, topic) == 0) {
    return; // just print of response for now
  }

  if (strcmp (rebootTopic, topic) == 0) {
    Serial.println("Rebooting...");
    ESP.restart();
  }
  // Relay 1
  if (strcmp (commandTopic, topic) == 0) {
    for (int i = 0; i < payloadLength; i++)
    {
      json1[i] = (char)payload[i];
      prev_json1[i] = (char)payload[i];

    }
    json1[payloadLength] = '\0';
    prev_json1[payloadLength] = '\0';
    Serial.println(json1);
  }
  // Relay 2
  if (strcmp (commandTopic2, topic) == 0) {
    for (int i = 0; i < payloadLength; i++)
    {
      json2[i] = (char)payload[i];
      prev_json2[i] = (char)payload[i];
    }
    json2[payloadLength] = '\0';
    prev_json2[payloadLength] = '\0';
    Serial.println(json2);
  }
  // Relay 3
  if (strcmp (commandTopic3, topic) == 0) {
    for (int i = 0; i < payloadLength; i++)
    {
      json3[i] = (char)payload[i];
      prev_json3[i] = (char)payload[i];

    }
    json3[payloadLength] = '\0';
    prev_json3[payloadLength] = '\0';
    Serial.println(json3);
  }
  // Relay 4
  if (strcmp (commandTopic4, topic) == 0) {
    for (int i = 0; i < payloadLength; i++)
    {
      json4[i] = (char)payload[i];
      prev_json4[i] = (char)payload[i];

    }
    json4[payloadLength] = '\0';
    prev_json4[payloadLength] = '\0';
    Serial.println(json4);
  }

  if (strcmp (updateTopic, topic) == 0) {
    handleUpdate(payload);
  }
}
void handleUpdate(byte* payload) {
  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject((char*)payload);
  if (!root.success()) {
    Serial.println("handleUpdate: payload parse FAILED");
    return;
  }
  Serial.println("handleUpdate payload:"); root.prettyPrintTo(Serial); Serial.println();

  JsonObject& d = root["d"];
  JsonArray& fields = d["fields"];
  for (JsonArray::iterator it = fields.begin(); it != fields.end(); ++it) {
    JsonObject& field = *it;
    const char* fieldName = field["field"];
    if (strcmp (fieldName, "metadata") == 0) {
      JsonObject& fieldValue = field["value"];
      if (fieldValue.containsKey("publishInterval")) {
        publishInterval = fieldValue["publishInterval"];
        Serial.print("publishInterval:");
        Serial.println(publishInterval);
      }
    }
  }
}
