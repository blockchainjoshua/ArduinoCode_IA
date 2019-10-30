
void wifiConnect() {

  //wifiManager.resetSettings();

  if (!wifiManager.autoConnect("IA-Kinex", "123"))
  {
    Serial.println("Failed to connect, we should reset as see if it connects");
    delay(3000);
    ESP.reset();
    delay(5000);

  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

