#include "RTClib.h"

#define MILLISECOND 1
#define SECOND 1000 * MILLISECOND
#define MINUTE 60 * SECOND

#define LOG_INTERVAL 2 * SECOND

RTC_DS1307 rtc;

void error(char *err) {
  Serial.print("error: ");
  Serial.println(err);
}

void log(DateTime now, char *msg) {
  Serial.print(now.unixtime());
  Serial.print(" ");
  Serial.println(msg);
}

void setup(void) {
  pinMode(13, OUTPUT);

  if (!rtc.begin()) {
    Serial.println("RTC failed");
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is not running");
  }
}

void loop(void) {
  Serial.begin(9600);

  log(rtc.now(), "hello");
  delay(LOG_INTERVAL);
}
