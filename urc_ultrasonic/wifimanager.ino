


void wifiConnect() {
  if (!wifiManager.autoConnect(wifimanager_ssid, wifimanager_password))
  {
    Serial.println("Failed to connect, we should reset and see if it connects");
    serialHTML += "Failed to connect, we should reset and see if it connects";
    delay(3000);
    ESP.reset();
    delay(5000);
  }
  Serial.println("");
  serialHTML += "";
  Serial.println("WiFi connected");
  serialHTML += "WiFi connected\n";
  Serial.print("IP address: ");
  serialHTML += "IP address: ";
  Serial.println(WiFi.localIP());
  ipAdd = ipToString(WiFi.localIP());
  serialHTML += ipToString(WiFi.localIP());
  Serial.print("MAC address: ");
  serialHTML += "\nMAC address: ";
  Serial.println(WiFi.macAddress());
  serialHTML += String(WiFi.macAddress());
  serialHTML += "\n\n";
}

void ResetSettings()
{
  digitalWrite(red_pin, HIGH);
  delay(1000);
  digitalWrite(red_pin, LOW);
  delay(1000);
  digitalWrite(red_pin, HIGH);
  delay(1000);
  digitalWrite(red_pin, LOW);
  delay(1000);
  digitalWrite(red_pin, HIGH);
  delay(1000);
  digitalWrite(red_pin, LOW);
  delay(1000);
  digitalWrite(red_pin, HIGH);
  digitalWrite(green_pin, LOW);
  wifiManager.resetSettings();
  ESP.reset();  //call reset

}
String ipToString(IPAddress ip) {
  String s = "";
  for (int i = 0; i < 4; i++)
    s += i  ? "." + String(ip[i]) : String(ip[i]);
  return s;
}
