void wifiConnect() {
  Serial.print("Connecting to "); Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("nWiFi connected, IP address: "); Serial.println(WiFi.localIP());
}

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
    Serial.println("subscribe to command OK");
  } else {
    Serial.println("subscribe to command FAILED");
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

  String payload = "{\"d\":{\"ultrasonic\":";
  payload += distance;
  payload += "}}";

  Serial.print("Sending payload: "); Serial.println(payload);

  if (client.publish(publishTopic, (char*) payload.c_str())) {
    Serial.println("Publish OK");
  } else {
    Serial.println("Publish FAILED");
  }
}

void callback(char* topic, byte* payload, unsigned int payloadLength) {
  Serial.print("callback invoked for topic: "); Serial.println(topic);

  if (strcmp (responseTopic, topic) == 0) {
    return; // just print of response for now
  }

  if (strcmp (rebootTopic, topic) == 0) {
    Serial.println("Rebooting...");
    ESP.restart();
  }
  if (strcmp (commandTopic, topic) == 0) {
    if (payload[0] == '1') {
      isActivatedReading = true;
    }
    else {
      isActivatedReading = false;
    }
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
        Serial.print("publishInterval:"); Serial.println(publishInterval);
      }
    }
  }
}
