/*
   Parsing the json and store it to a variable
   This function is checking if the setted time and day timer is equal to current time and day.
   If the setted timer is equal to the current time and day the relay or light will turn on.

   Author: Joshua Malabanan
*/
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
  /////Relay 1 Checker
  if ((timeNow == timeOn) && (id == 1) && (day1 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 1) && (day2 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 1) && (day3 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 1) && (day4 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 1) && (day5 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 1) && (day6 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 1) && (day7 == daysOfTheWeek[timeClient.getDay()])) {
    relay1Status = true;
  }
  if ((timeNow == timeOn) && (id == 1) && (day1 == "E")) {
    relay1Status = true;
  }
  if ((timeNow == timeOff) && (id == 1) && (day1 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 1) && (day2 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 1) && (day3 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 1) && (day4 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 1) && (day5 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 1) && (day6 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 1) && (day7 == daysOfTheWeek[timeClient.getDay()])) {
    relay1Status = false;
  }
  /////Relay 2 Checker
  if ((timeNow == timeOn) && (id == 2) && (day1 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 2) && (day2 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 2) && (day3 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 2) && (day4 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 2) && (day5 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 2) && (day6 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 2) && (day7 == daysOfTheWeek[timeClient.getDay()])) {
    relay2Status = true;
  }
  if ((timeNow == timeOn) && (id == 2) && (day1 == "E")) {
    relay2Status = true;
  }
  if ((timeNow == timeOff) && (id == 2) && (day1 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 2) && (day2 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 2) && (day3 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 2) && (day4 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 2) && (day5 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 2) && (day6 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 2) && (day7 == daysOfTheWeek[timeClient.getDay()])) {
    relay2Status = false;
  }
  /////Relay 3 Checker
  if ((timeNow == timeOn) && (id == 3) && (day1 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 3) && (day2 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 3) && (day3 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 3) && (day4 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 3) && (day5 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 3) && (day6 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 3) && (day7 == daysOfTheWeek[timeClient.getDay()])) {
    relay3Status = true;
  }
  if ((timeNow == timeOn) && (id == 3) && (day1 == "E")) {
    relay3Status = true;
  }
  if ((timeNow == timeOff) && (id == 3) && (day1 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 3) && (day2 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 3) && (day3 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 3) && (day4 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 3) && (day5 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 3) && (day6 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 3) && (day7 == daysOfTheWeek[timeClient.getDay()])) {
    relay3Status = false;
  }
  /////Relay 4 Checker
  if ((timeNow == timeOn) && (id == 4) && (day1 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 4) && (day2 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 4) && (day3 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 4) && (day4 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 4) && (day5 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 4) && (day6 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOn) && (id == 4) && (day7 == daysOfTheWeek[timeClient.getDay()])) {
    relay4Status = true;
  }
  if ((timeNow == timeOn) && (id == 4) && (day1 == "E")) {
    relay4Status = true;
  }
  if ((timeNow == timeOff) && (id == 4) && (day1 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 4) && (day2 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 4) && (day3 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 4) && (day4 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 4) && (day5 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 4) && (day6 == daysOfTheWeek[timeClient.getDay()]) || (timeNow == timeOff) && (id == 4) && (day7 == daysOfTheWeek[timeClient.getDay()])) {
    relay4Status = false;
  }
  strncpy(json1, prev_json1, 256);
  strncpy(json2, prev_json2, 256);
  strncpy(json3, prev_json3, 256);
  strncpy(json4, prev_json4, 256);
}
