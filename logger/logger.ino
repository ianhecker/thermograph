#include "RTClib.h"

// PINS ------------------------------------------------------------------------
#define NOTIFY_LED 13

// TIME ------------------------------------------------------------------------
#define MILLISECOND 1
#define SECOND 1000 * MILLISECOND
#define MINUTE 60 * SECOND
#define LOG_INTERVAL 2 * SECOND

RTC_DS1307 rtc;

// DEBUG LOGS ------------------------------------------------------------------
byte DEBUG_LOG_OUTPUT = 0b00;
#define DEBUG_LOG_OFF = 0b00
#define DEBUG_LOG_SERIAL 0b01
#define DEBUG_LOG_FILE 0b10
#define DEBUG_LOG_SERIAL_AND_FILE 0b11

// ERROR -----------------------------------------------------------------------
void error(char *err) {
  Serial.print("error: ");
  Serial.println(err);
}

// LED NOTIFICATIONS -----------------------------------------------------------
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

// LOGGING ---------------------------------------------------------------------
void logSerial(String log) { Serial.println(log); }

void logFile(String log) {
  // LOG TO SD STUB
  Serial.println(log);
}

// DEBUG LOGGING ---------------------------------------------------------------
struct Debug {

  void logCtxAndTemperature(DateTime now, String ctx, float temp) {
    char buffer[100];
    char tempBuffer[10];
    dtostrf(temp, 6, 2, tempBuffer);

    char fmt[50] = "unix:'%lu' | context:'%s' | temperature:'%s'";
    sprintf(buffer, fmt, now.unixtime(), ctx.c_str(), tempBuffer);

    log(String(buffer));
  }

  void logCtx(DateTime now, String ctx) {
    char buffer[100];

    char fmt[50] = "unix:'%lu' | context:'%s'";
    sprintf(buffer, fmt, now.unixtime(), ctx.c_str());

    log(String(buffer));
  }

  void log(String msg) {

    if (DEBUG_LOG_OUTPUT & DEBUG_LOG_SERIAL) {
      logSerial(msg);
    }
    if (DEBUG_LOG_OUTPUT & DEBUG_LOG_FILE) {
      logFile(msg);
    }
  }
};

// TEMPERATURE -----------------------------------------------------------------
float getTemperature() {
  // TEMPERATURE SENSOR STUB

  float temperature = 101.234;

  return temperature;
}

void writeTemperature(float temperature) {
  // SD CARD WRITE STUB
}

// SETUP -----------------------------------------------------------------------
void setup(void) {
  pinMode(NOTIFY_LED, OUTPUT);

  if (!rtc.begin()) {
    Serial.println("RTC failed");
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is not running");
  }

  DEBUG_LOG_OUTPUT = DEBUG_LOG_SERIAL;
}

// LOOP ------------------------------------------------------------------------
void loop(void) {
  Serial.begin(9600);
  Debug debug;

  float temperature = getTemperature();

  debug.logCtxAndTemperature(rtc.now(), "took temp", temperature);

  writeTemperature(temperature);

  debug.logCtxAndTemperature(rtc.now(), "wrote temp to SD card", temperature);

  // notify_write();

  delay(5 * SECOND);
}
