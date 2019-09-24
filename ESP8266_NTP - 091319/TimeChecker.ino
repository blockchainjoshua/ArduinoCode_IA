void TimeChecker(char _json[]) {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(_json);
  int timeOn = root["timeOn"];
  int timeOff = root["timeOff"];
  String day1 = root["days"][0];
  String day2 = root["days"][1];
  String day3 = root["days"][2];
  String day4 = root["days"][3];
  String day5 = root["days"][4];
  String day6 = root["days"][5];
  String day7 = root["days"][6];
  int id = root["id"];
  if ((timeNow == timeOn) && (id == 1) && (day1 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 1) && (day2 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 1) && (day3 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 1) && (day4 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 1) && (day5 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 1) && (day6 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 1) && (day7 == daysOfTheWeek[timeClient.getDay()])) {
    relay1Status = true;
  }
  if ((timeNow == timeOn) && (id == 1) && (day1 == "E")) {
    relay1Status = true;
  }
  if ((timeNow == timeOff) && (id == 1) && (day1 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 1) && (day2 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 1) && (day3 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 1) && (day4 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 1) && (day5 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 1) && (day6 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 1) && (day7 == daysOfTheWeek[timeClient.getDay()])) {
    relay1Status = false;
  }
  //
  if ((timeNow == timeOn) && (id == 2) && (day1 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 2) && (day2 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 2) && (day3 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 2) && (day4 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 2) && (day5 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 2) && (day6 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 2) && (day7 == daysOfTheWeek[timeClient.getDay()])) {
    relay2Status = true;
  }
  if ((timeNow == timeOn) && (id == 2) && (day1 == "E")) {
    relay2Status = true;
  }
  if ((timeNow == timeOff) && (id == 2) && (day1 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 2) && (day2 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 2) && (day3 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 2) && (day4 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 2) && (day5 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 2) && (day6 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 2) && (day7 == daysOfTheWeek[timeClient.getDay()])) {
    relay2Status = false;
  }
  Serial.println(timeOff);
  strncpy(json1, prev_json1, 256);
  strncpy(json2, prev_json2, 256);
}
