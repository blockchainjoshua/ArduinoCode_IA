#include <RHReliableDatagram.h>
#include <RH_RF95.h>
#include <SPI.h>
#include <Wire.h>
#include "config.h"


RH_RF95 driver;
//RH_RF95 driver(D8, D2);
RHReliableDatagram manager(driver, CLIENT_ADDRESS);

int SERVER_ADDRESS;

uint8_t data[] = "John Benedict Rillo";
char CurrentStatus[8] = "OUT";
uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];

void setup()
{
  Serial.begin(9600);
  Serial.println("initializing");
   strncpy(CurrentStatus, "OUT", 8);
  if (!manager.init())
    Serial.println("init failed");
  Serial.println("Setting freq");
  driver.setFrequency(433.0);
  driver.setTxPower(23, false);
  driver.setModemConfig(RH_RF95::Bw31_25Cr48Sf512);
  manager.setTimeout(2000);
}

void loop()
{
  LoraReceiver();
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
void LoraReceiver()
{
  if (manager.available())
  {
    uint8_t len = sizeof(buf);
    uint8_t from;
    if (manager.recvfromAck(buf, &len, &from))
    {
      Serial.print("Current status: ");
      Serial.println((char*)CurrentStatus);
      Serial.print("got message from gateway: 0x");
      Serial.print(from, HEX);
      Serial.print(" : RSSI ");
      Serial.print(driver.lastRssi());
      Serial.print(" : ");
      Serial.println((char*)buf);
    }
  }
}
