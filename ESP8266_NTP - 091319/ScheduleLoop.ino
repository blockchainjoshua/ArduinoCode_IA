void ScheduleLoop()
{
  timeClient.update();

    _hour  = String(timeClient.getHours());
  
  if (timeClient.getMinutes() < 10|| timeClient.getMinutes() == 0) {
    _minute = "0" +  String(timeClient.getMinutes());
  }
  else {
    _minute = String(timeClient.getMinutes());
  }
  if (timeClient.getSeconds() < 10 || timeClient.getSeconds() == 0) {
    _second = "0" +  String(timeClient.getSeconds());
  }
  else {
    _second = String(timeClient.getSeconds());
  }
  _timeNow = String(_hour + _minute + _second);
  timeNow = _timeNow.toInt();

  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.println(", " + _hour + ":" + _minute + ":" + _second);
}
