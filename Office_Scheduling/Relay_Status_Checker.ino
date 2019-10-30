/*
 * Checking the status of relay if the status of relay is equal
 * to true relay switch on and if relay status is equal to false
 * relay will swicth off.
 * 
  * Author: Joshua Malabanan
 */


void RelayStatusChecker() {
  if (relay1Status == true) {
    Serial.println("RELAY 1 IS ON!!!!");
  }
  else if (relay1Status == false) {
    Serial.println("RELAY 1 IS OFF!!!!");
  }
  if (relay2Status == true) {
    Serial.println("RELAY 2 IS ON!!!!");
  }
  else if (relay2Status == false) {
    Serial.println("RELAY 2 IS OFF!!!!");
  }

    if (relay3Status == true) {
    Serial.println("RELAY 3 IS ON!!!!");
  }
  else if (relay3Status == false) {
    Serial.println("RELAY 3 IS OFF!!!!");
  }
    if (relay4Status == true) {
    Serial.println("RELAY 4 IS ON!!!!");
  }
  else if (relay4Status == false) {
    Serial.println("RELAY 4 IS OFF!!!!");
  }
}
