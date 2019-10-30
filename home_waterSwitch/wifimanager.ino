
void wifiConnect() {

   //wifiManager.resetSettings();
   
  if (!wifiManager.autoConnect(wifimanager_ssid, wifimanager_password))
  {
    Serial.println("Failed to connect, we should reset and see if it connects");
    delay(3000);
    ESP.reset();
    delay(5000);

  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());

}

void ResetSettings()
{

  //blink the red 3x
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

