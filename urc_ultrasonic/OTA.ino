/*
   OTA
   Used to remotely flash firmware

*/

ESP8266WebServer ota_server(80);
//const char* serverIndex = "<form method='POST' action='/update' enctype='multipart/form-data'><p>"DEVICE_ID"</p><input type='file' name='update'><input type='submit' value='Update'></form>";
String SendOTA() {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>"DEVICE_ID" Serial Monitor ""</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #ffbf00;margin: 50px auto 30px;} h6 {color: white} div {background:#1e1f26 } a {color:white}\n";
  ptr += "p {font-size: 24px;color: white;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body bgcolor=\"#1d1e22\">\n";
  ptr += "<h1>"DEVICE_ID" Over The Air Update</h1>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<form method='POST' action='/update' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>";
  ptr += "<br><br><h4><a href=\"http://";
  ptr += ipAdd;
  ptr += "/\">Home</a><h4>\n";
  ptr += "</div>\n";
  ptr += "</head>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
String MainPage() {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>"DEVICE_ID" Main Page ""</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #ffbf00;margin: 50px auto 30px;} .content h4{color:white; }div{background:#1e1f26 } a {color:white}\n";
  ptr += "p {font-size: 24px;color: white;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body bgcolor=\"#1d1e22\">\n";
  ptr += "<h1>"DEVICE_ID" Main Page</h1>\n";
  ptr += "<div class=\"content\" id=\"webpage\">\n";
  ptr += "<h4>IP Address : ";
  ptr += ipAdd;
  ptr += "<br><h4>Mac Address : ";
  ptr += String(WiFi.macAddress());
  ptr += "<h4><br>";
  ptr += "<h2><a href=\"http://";
  ptr += ipAdd;
  ptr += "/login\">OTA Update</a></h2>\n";
  ptr += "<h2><a href=\"http://";
  ptr += ipAdd;
  ptr += "/serial\">Serial Monitor</a></h2>\n";
  ptr += "</div>\n";
  ptr += "</head>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
String SendLogin() {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>"DEVICE_ID" Main Page ""</title>\n";
  ptr += "<style>html { font-family: Helve  tica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #ffbf00;margin: 50px auto 30px;} h2{color: white} div {background:#1e1f26 } a{color:white}\n";
  ptr += "p {font-size: 24px;color: white;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body bgcolor=\"#1d1e22\">\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>"DEVICE_ID" OTA Login</h1>\n";
  ptr += "<form name=\"login\"><input type=\"text\"name=\"userid\" placeholder=\"Username\"/><br><br><input type=\"password\"name=\"pswrd\"placeholder=\"Password\"/><br><br><br><input type=\"button\"onclick=\"check(this.form)\"value=\"Login\"/><input type=\"reset\"value=\"Cancel\"/></form>";
  ptr += "<script language=\"javascript\">function check(form){if(form.userid.value == \"iot\" && form.pswrd.value == \"3201antel\"){window.open('ota','_self') }else {alert(\"Error Password or Username\")}}</script>";
  ptr += "<br><br><h4><a href=\"http://";
  ptr += ipAdd;
  ptr += "/\">Home</a><h4>\n";
  ptr += "</div>\n";
  ptr += "</head>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
String SendHTML() {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" http-equiv=\"refresh\" content=\"3\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>"DEVICE_ID" Serial Monitor ""</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #ffbf00;margin: 50px auto 30px;} div {background:#1e1f26 } a {color:white}\n";
  ptr += "p {font-size: 24px;color: white;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body bgcolor=\"#1d1e22\">\n";
  ptr += "<h1>"DEVICE_ID" Serial Monitor</h1>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<textarea style=\"font-size: 15pt\" rows=\"30\" cols=\"100\">";
  ptr += serialHTML;
  ptr += "</textarea>";
  ptr += "<br><br><h4><a href=\"http://";
  ptr += ipAdd;
  ptr += "/\">Home</a><h4>\n";
  ptr += "</div>\n";
  ptr += "</head>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
void InitOTAServer()
{
  ota_server.on("/", HTTP_GET, []() {
    ota_server.sendHeader("Connection", "close");
    ota_server.send(200, "text/html", MainPage());
  });
  ota_server.on("/ota", HTTP_GET, []() {
    ota_server.sendHeader("Connection", "close");
    ota_server.send(200, "text/html", SendOTA());
  });
  ota_server.on("/serial", HTTP_GET, []() {
    ota_server.sendHeader("Connection", "close");
    ota_server.send(200, "text/html", SendHTML());
  });
  ota_server.on("/login", HTTP_GET, []() {
    ota_server.sendHeader("Connection", "close");
    ota_server.send(200, "text/html", SendLogin());
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
