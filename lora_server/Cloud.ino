
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

  client.subscribe("iotdm-1/response");
  client.subscribe("iotdm-1/device/update");

  if (client.subscribe(switch1Topic))
  {
    Serial.println("Switch 1 topic subscribed");
  }

  if (client.subscribe(switch2Topic))
  {
    Serial.println("Switch 2 topic subscribed");
  }

  if (client.subscribe(switch3Topic))
  {
    Serial.println("Switch 3 topic subscribed");
  }

  if (client.subscribe(switch4Topic))
  {
    Serial.println("Switch 4 topic subscribed");
  }

  if (client.subscribe(energyTopic))
  {
    Serial.println("Energy topic subscribed");
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

  //prepare message payload
  char messagePayload[MESSAGE_MAX_LEN];

  //retrieve temperature reading
  readTemp(messagePayload);

  Serial.print("Sending payload: ");
  Serial.println(messagePayload);

  if (client.publish(publishTopic, (char*) messagePayload))
  {
    Serial.println("Publish OK");
  }

  else
  {
    Serial.println("Publish FAILED");
  }
}

void callback(char* topic, byte * payload, unsigned int payloadLength)
{
  Serial.print("callback invoked for topic: "); Serial.println(topic);

  if (strcmp(switch1Topic, topic) == 0)
  {
    if (payload[0] == '1')
    {
      LoraSend("relay1:on", CLIENT_ADDRESS_RELAYS);
    }

    else
    {
      LoraSend("relay1:off", CLIENT_ADDRESS_RELAYS);
    }
  }

  if (strcmp(switch2Topic, topic) == 0)
  {
    if (payload[0] == '1')
    {
      LoraSend("relay2:on", CLIENT_ADDRESS_RELAYS);
    }

    else
    {
      LoraSend("relay2:off", CLIENT_ADDRESS_RELAYS);
    }
  }

  if (strcmp(switch3Topic, topic) == 0)
  {
    if (payload[0] == '1')
    {
      LoraSend("relay3:on", CLIENT_ADDRESS_RELAYS);
    }

    else
    {
      LoraSend("relay3:off", CLIENT_ADDRESS_RELAYS);
    }
  }

  if (strcmp(switch4Topic, topic) == 0)
  {
    if (payload[0] == '1')
    {
      LoraSend("relay4:on", CLIENT_ADDRESS_RELAYS);
    }

    else
    {
      LoraSend("relay4:off", CLIENT_ADDRESS_RELAYS);
    }
  }

  if (strcmp(energyTopic, topic) == 0)
  {
    LoraSend("getreading", CLIENT_ADDRESS_ENERGY_METER);
  }
}
