/*
   Barcode logic
*/

#include <SoftwareSerial.h>

String inputString = "";

SoftwareSerial swSer(rx_pin, tx_pin, false, 128); //Define hardware connections

void initBarcode()
{
  swSer.begin(sw_baud);

#ifdef DEBUG
  Serial.println("\nSoftware serial started");
#endif

}

void HandleBarcode()
{
  if (swSer.available())
  {
    while (swSer.available() > 0) {  //wait for data at software serial
      char inChar = swSer.read();

      delay(10);
      if ((inChar != '\n') || (inChar != '\r'))
      {
        inputString += inChar;
      }
        

      if (inChar == '\r') {
        constructData();
      }
    }
  }
}

void constructData()
{
  char payload[256];
  char timestamp[128];
  currentTime(timestamp);
  StaticJsonBuffer<256> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["barcode"] = inputString;
  root["ip"] = ipToString(WiFi.localIP());
  root["timestamp"] = timestamp;
  root.printTo(payload, 256);
  publishData(payload, publishTopic);
  inputString = "";
}

