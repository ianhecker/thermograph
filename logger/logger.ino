#include "RTClib.h"

#define MILLISECOND 1
#define SECOND 1000 * MILLISECOND
#define MINUTE 60 * SECOND
#define LOG_INTERVAL 2 * SECOND

#define NOTIFY_LED 13

RTC_DS1307 rtc;

void error(char *err) {
  Serial.print("error: ");
  Serial.println(err);
}

void blink(int pin, int duration) {
  digitalWrite(pin, HIGH);
  delay(duration);
  digitalWrite(pin, LOW);
}

void notify() {
  blink(NOTIFY_LED, 200 * MILLISECOND);
  delay(200 * MILLISECOND);
  blink(NOTIFY_LED, 200 * MILLISECOND);
  return;
}

void log(DateTime now, String msg) {
  Serial.print("unix='" + String(now.unixtime()) + "',");
  Serial.print("context='" + msg + "'");
  Serial.println();
  return;
}

float getTemperature() {
  float temperature = 72.23;
  log(rtc.now(), "took temperature:" + String(temperature) + " degrees");

  return temperature;
}

void writeTemperature(float temperature) {
  log(rtc.now(), "wrote temperature:" + String(temperature) + " to memory");
  return;
}

void setup(void) {
  pinMode(NOTIFY_LED, OUTPUT);

  if (!rtc.begin()) {
    Serial.println("RTC failed");
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is not running");
  }
}

void loop(void) {
  Serial.begin(9600);

  float temperature = getTemperature();

  writeTemperature(temperature);
  notify();

  delay(1 * SECOND);
}
