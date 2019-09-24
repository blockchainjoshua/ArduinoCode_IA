#include <ArduinoJson.h>

void setup() {
  Serial.begin(9600);
 const size_t bufferSize = JSON_ARRAY_SIZE(5) + 2*JSON_OBJECT_SIZE(5) + 70;
DynamicJsonBuffer jsonBuffer(bufferSize);

const char* json = "[{\"sensor\":\"gps1\",\"time\":102130},{\"sensor\":\"gps1\",\"time\":1351824120}]";

JsonArray& root = jsonBuffer.parseArray(json);

String root_0_sensor = root[0]["sensor"]; // "gps1"
long root_0_time = root[0]["time"]; // 1351824120

String root_1_sensor = root[1]["sensor"]; // "gps1"
long root_1_time = root[1]["time"]; // 1351824120
Serial.println(root_0_sensor);
Serial.println(root_0_time);
Serial.println(root_1_sensor);
Serial.println(root_1_time);

}
void loop(){

  
}
