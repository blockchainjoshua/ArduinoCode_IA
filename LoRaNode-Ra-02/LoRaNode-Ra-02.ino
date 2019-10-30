
// Use ESP declarations. This sketch does not use WiFi stack of ESP
//  #include <ESP8266WiFi.h>
#include <ESP.h>
#include <Base64.h>

// All specific changes needed for ESP8266 need be made in hal.cpp if possible
// Include ESP environment definitions in lmic.h (lmic/limic.h) if needed
#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>

// LoRaWAN Application identifier (AppEUI)
// Not used in this example
static const u1_t APPEUI[8]  = { 0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x02, 0x38, 0xE7 };

// LoRaWAN DevEUI, unique device ID (LSBF)
// Not used in this example
static const u1_t DEVEUI[8]  = { 0x00, 0x71, 0x53, 0x8B, 0xE0, 0xD0, 0xC0, 0x91 };

// LoRaWAN NwkSKey, network session key 
// Use this key for The Things Network
static const u1_t DEVKEY[16] = { 0xBC, 0x2D, 0xDA, 0xB3, 0xF6, 0xD4, 0x29, 0x68, 0x19, 0x78, 0x82, 0xF3, 0xE5, 0x70, 0x26, 0xE4 };

// LoRaWAN AppSKey, application session key
// Use this key to get your data decrypted by The Things Network
static const u1_t ARTKEY[16] = { 0x2C, 0xD3, 0x0F, 0xFA, 0x12, 0xDD, 0x7B, 0x76, 0xD5, 0x7A, 0xE2, 0xE6, 0xAB, 0x14, 0x16, 0x01 };

// LoRaWAN end-device address (DevAddr)
// See http://thethingsnetwork.org/wiki/AddressSpace
static const u4_t DEVADDR = 0x26011F68 ; // <-- Change this address for every node! ESP8266 node 0x01

//////////////////////////////////////////////////
// APPLICATION CALLBACKS
//////////////////////////////////////////////////

// provide application router ID (8 bytes, LSBF)
void os_getArtEui (u1_t* buf) {
    memcpy(buf, APPEUI, 8);
}

// provide device ID (8 bytes, LSBF)
void os_getDevEui (u1_t* buf) {
    memcpy(buf, DEVEUI, 8);
}

// provide device key (16 bytes)
void os_getDevKey (u1_t* buf) {
    memcpy(buf, DEVKEY, 16);
}

uint8_t mydata[] = "Hello ESP8266 world!";
static osjob_t sendjob;

// Pin mapping
// XXX We have to see whether all these pins are really used
// if not, we can use them for real sensor work.

//const lmic_pinmap lmic_pins = {
//  .nss = 15,      // Make D8/GPIO15, is nSS on ESP8266
//  .rxtx = 2,      // D4/GPIO2. For placeholder only,
//            // Do not connected on RFM92/RFM95
//  .rst = 16,       // Make D0/GPIO16, Needed on RFM92/RFM95? (probably not)
//  .dio = {5, 4, 0},   // Specify pin numbers for DIO0, 1, 2
//            // D1/GPIO5,D2/GPIO4,D3/GPIO3 are usable pins on ESP8266
//            // NOTE: D3 not really usable when UART not connected
//            // As it is used during bootup and will probably not boot.
//            // Leave D3 Pin unconnected for sensor to work
//};
//HEYYYY


const lmic_pinmap lmic_pins = {
    .nss = D8,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 4,
    .dio = {D2, LMIC_UNUSED_PIN, LMIC_UNUSED_PIN},
};


void onEvent (ev_t ev) {
    //debug_event(ev);

    switch(ev) {
      // scheduled data sent (optionally data received)
      // note: this includes the receive window!
      case EV_TXCOMPLETE:
          // use this event to keep track of actual transmissions
          Serial.print("Event EV_TXCOMPLETE, time: ");
          Serial.println(millis() / 1000);
          if(LMIC.dataLen) { // data received in rx slot after tx
              //debug_buf(LMIC.frame+LMIC.dataBeg, LMIC.dataLen);
              Serial.println("Data Received!");
          }
          break;
       default:
          break;
    }
}

void do_send(osjob_t* j){
      Serial.print("Time: ");
      Serial.println(millis() / 1000);
      // Show TX channel (channel numbers are local to LMIC)
      Serial.print("Send, txCnhl: ");
      Serial.println(LMIC.txChnl);
      Serial.print("Opmode check: ");
      // Check if there is not a current TX/RX job running
    if (LMIC.opmode & (1 << 7)) {
      Serial.println("OP_TXRXPEND, not sending");
    } else {
      Serial.println("ok");
      // Prepare upstream data transmission at the next possible time.
      LMIC_setTxData2(1, mydata, sizeof(mydata)-1, 0);
    }
    // Schedule a timed job to run at the given timestamp (absolute system time)
    os_setTimedCallback(j, os_getTime()+sec2osticks(5), do_send);
         
}

// Remove the Serial messages once the unit is running reliable
// 
void setup() {
  Serial.begin(115200);
  Serial.println("Starting");
  
  // LMIC init
  os_init();
  Serial.println("os_init() finished");
  
  // Reset the MAC state. Session and pending data transfers will be discarded.
  LMIC_reset();
  Serial.println("LMIC_reset() finished");
  
  // Set static session parameters. Instead of dynamically establishing a session 
  // by joining the network, precomputed session parameters are be provided.
  LMIC_setSession (0x1, DEVADDR, (uint8_t*)DEVKEY, (uint8_t*)ARTKEY);
  Serial.println("LMIC_setSession() finished");
  
  // Disable data rate adaptation
  LMIC_setAdrMode(0);
  Serial.println("LMICsetAddrMode() finished");
  
  // Disable link check validation
  LMIC_setLinkCheckMode(0);
  // Disable beacon tracking
  LMIC_disableTracking ();
  // Stop listening for downstream data (periodical reception)
  LMIC_stopPingable();
  // Set data rate and transmit power (note: txpow seems to be ignored by the library)
  LMIC_setDrTxpow(DR_SF7,14);
  //
  //Serial.flush();
  Serial.println("Init done");
}

// Same loop as used in original sketch. Modify for ESP8266 sensor use.
//
void loop() {

do_send(&sendjob);
delay(10);

while(1) {
  os_runloop_once();
  delay(1000);
  }
}
