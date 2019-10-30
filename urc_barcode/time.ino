#include <NTPClient.h>
#include <WiFiUdp.h>

//Philippines timezone
//For UTC +8.00 : 8 * 60 * 60 : 28800
const long utcOffsetInSeconds = 28800;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void initTime()
{
  timeClient.begin();
  timeClient.update();
#ifdef DEBUG

  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
#endif

}

void currentTime(char * t)
{
  timeClient.update();
  sprintf(t, "%d:%d:%d", timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds());
}

