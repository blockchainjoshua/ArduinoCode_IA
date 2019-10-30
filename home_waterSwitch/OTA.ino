/*
   OTA
   Used to remotely flash firmware

*/

ESP8266WebServer ota_server(80);
const char* serverIndex = "<form method='POST' action='/update' enctype='multipart/form-data'><p>"DEVICE_ID"</p><input type='file' name='update'><input type='submit' value='Update'></form>";

void InitOTAServer()
{
  ota_server.on("/", HTTP_GET, []() {
    ota_server.sendHeader("Connection", "close");
    ota_server.send(200, "text/html", serverIndex);
  });
  ota_server.on("/update", HTTP_POST, []() {
    ota_server.sendHeader("Connection", "close");
    ota_server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    delay(1000);
    ESP.restart();
  }, []() {
    HTTPUpload& upload = ota_server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.setDebugOutput(true);
      WiFiUDP::stopAll();
      Serial.printf("Update: %s\n", upload.filename.c_str());
      uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
      if (!Update.begin(maxSketchSpace)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
      Serial.setDebugOutput(false);
    }
    yield();
  });
  ota_server.begin();
}

void HandleOTAServer()
{
  ota_server.handleClient();
}
