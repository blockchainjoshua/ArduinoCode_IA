
RH_RF95 driver(D8, D2);
RHReliableDatagram manager(driver, SERVER_ADDRESS);

uint8_t data[8] = "OUT";
uint8_t far[8] = "FAR";
uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];

void LoraInit()
{
  if (!manager.init()){
  Serial.println("lora failed");
  }
  else{
    Serial.println("lora success");
    }
  Serial.println("Setting freq");
  driver.setFrequency(433.0);
  driver.setTxPower(23, false);
  driver.setModemConfig(RH_RF95::Bw31_25Cr48Sf512);
  manager.setTimeout(1000);
  
}

void LoraServer()
{
  if (manager.available())
  {
    uint8_t len = sizeof(buf);
    uint8_t from;
    if (manager.recvfromAck(buf, &len, &from))
    {
      Serial.print("got reply from : 0x");
      Serial.print(from, HEX);
      Serial.print(" : RSSI ");
      Serial.print(driver.lastRssi());
      Serial.print(" : ");
      Serial.println((char*)buf);

      //device must be nearby to send attendance to cloud
      if (driver.lastRssi() > RSSI_LIMIT)
      {
        //construct json to send to cloud
        char message[256];
        StaticJsonBuffer<256> jsonBuffer;
        JsonObject& root = jsonBuffer.createObject();
        root["data"] = (char*)buf;
        root.printTo(message, MESSAGE_MAX_LEN);

        if (client.publish(publishLoraTopic, (char*)message))
        {
          Serial.println("Publish OK");
        }

        else
        {
          Serial.println("Publish FAILED");
        }

        if (!manager.sendtoWait(data, sizeof(data), from))
          Serial.println("No packets received");
      }

      else {
        Serial.println("Device is far. Not sending attendance log");

        if (!manager.sendtoWait(far, sizeof(far), from))
          Serial.println("No packets received");
      }
    }
  }
}

void LoraSend(String cmd, int address)
{
  char message[32];
  cmd.toCharArray(message, sizeof(message));
  if (manager.sendtoWait((uint8_t*)message, sizeof(message), address))
  {
    uint8_t len = sizeof(buf);
    uint8_t from;
    if (manager.recvfromAckTimeout(buf, &len, 2000, &from))
    {
      Serial.print("Reply from : 0x");
      Serial.print(from, HEX);
      Serial.print(" : RSSI ");
      Serial.print(driver.lastRssi());
      Serial.print(" : ");
      Serial.println((char*)buf);
    }
  }
  else {
    Serial.println("No Response");
  }
}
