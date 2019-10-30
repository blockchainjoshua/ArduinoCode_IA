
float temp = 0.00;
int counter = 0;

void readTemp(char *payload)
{

  //get random temp
  temp = random(28, 30) + random(1, 99) / 100.0;

  //construct json response
  StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
  JsonObject &root = jsonBuffer.createObject();

  Serial.print("Temperature: ");
  Serial.println(temp);

  root["temperature"] = temp;
  root.printTo(payload, MESSAGE_MAX_LEN);
}
