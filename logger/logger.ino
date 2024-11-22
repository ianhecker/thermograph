#include "RTClib.h"

#define NOTIFY_LED 13

#define MILLISECOND 1
#define SECOND 1000 * MILLISECOND
#define MINUTE 60 * SECOND
#define LOG_INTERVAL 2 * SECOND

RTC_DS1307 rtc;

void error(char *err) {
  Serial.print("error: ");
  Serial.println(err);
}

void blink(int pin, int delay_ms) {
  digitalWrite(pin, HIGH);
  delay(delay_ms);
  digitalWrite(pin, LOW);
}

void double_blink(int pin, int blink_ms, int delay_ms) {
  blink(pin, blink_ms);
  delay(delay_ms);
  blink(pin, blink_ms);
}

void notify_write() {
  double_blink(NOTIFY_LED, 200 * MILLISECOND, 200 * MILLISECOND);
}
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
