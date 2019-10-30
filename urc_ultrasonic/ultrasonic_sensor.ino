

void InitSensor()
{
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
}

void SensorLoop()
{
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  currentDistance = (duration / 2) / 29.1;
 
  if (lastDistance == currentDistance)
  {
    stabilityCount++;
    lastDistance = currentDistance;
  }

  else {
    stabilityCount = 0;
    lastDistance = currentDistance;
  }
}
