int pin = 6;
void setup() {
  pinMode(pin , OUTPUT);
  Serial.begin(9600);
  digitalWrite(pin, LOW);
}

void loop() {
  if (Serial.available() > 0 ) {
    String recieved = Serial.readString();
    if (recieved.indexOf("ON") != -1 )
    {
      Serial.println("LED is ON");
      digitalWrite(pin, HIGH);
    }
    else if (recieved.indexOf("OFF") != -1 )
    {
      Serial.println("LED is ON");
      digitalWrite(pin, LOW);
    }
    delay(100);
  }
}
