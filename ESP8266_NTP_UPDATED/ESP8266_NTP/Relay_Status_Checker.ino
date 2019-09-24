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
}
