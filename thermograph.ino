#include <RTClib.h>
#include <SD.h>

// PINS ------------------------------------------------------------------------
#define NOTIFY_LED 13

// TIME ------------------------------------------------------------------------
#define MILLISECOND 1
#define SECOND 1000 * MILLISECOND
#define MINUTE 60 * SECOND
#define LOG_INTERVAL 2 * SECOND

RTC_PCF8523 rtc;

char DAYS_OF_THE_WEEK[7][12] = {"Sunday",   "Monday", "Tuesday", "Wednesday",
                                "Thursday", "Friday", "Saturday"};

// DEBUG LOGS ------------------------------------------------------------------
byte DEBUG_LOG_OUTPUT = 0b00;
#define DEBUG_LOG_OFF = 0b00
#define DEBUG_LOG_SERIAL 0b01
#define DEBUG_LOG_FILE 0b10
#define DEBUG_LOG_SERIAL_AND_FILE 0b11

// SD --------------------------------------------------------------------------
File logfile;

// ERROR -----------------------------------------------------------------------
void error(char *err) {
  Serial.print("error: ");
  Serial.println(err);
  Serial.flush();
  while (1)
    delay(10);
}

// LED NOTIFICATIONS -----------------------------------------------------------
void Blink(int pin, int delay_ms) {
  digitalWrite(pin, HIGH);
  delay(delay_ms);
  digitalWrite(pin, LOW);
}

void DoubleBlink(int pin, int blink_ms, int delay_ms) {
  Blink(pin, blink_ms);
  delay(delay_ms);
  Blink(pin, blink_ms);
}

void NotifyWrite() {
  DoubleBlink(NOTIFY_LED, 200 * MILLISECOND, 200 * MILLISECOND);
}

// LOGGING ---------------------------------------------------------------------
void LogSerial(String log) { Serial.println(log); }

void LogFile(String log) {
  // LOG TO SD STUB
  Serial.println(log);
}

// Data Formatting -------------------------------------------------------------
struct fmt {

  String RTCToHumanReadable(DateTime dt) {
    char buffer[100];
    char fmt[50] = "%d/%02d/%02d %s %02d:%02d:%02d";

    char *dayOfTheWeek = DAYS_OF_THE_WEEK[dt.dayOfTheWeek()];

    sprintf(buffer, fmt, dt.year(), dt.month(), dt.day(), dayOfTheWeek,
            dt.hour(), dt.minute(), dt.second());

    return String(buffer);
  }

  String TimestampAndDate(DateTime time) {
    char buffer[50];
    char fmt[30] = "unix:'%lu' | date:'%s'";

    sprintf(buffer, fmt, time.unixtime(), RTCToHumanReadable(time).c_str());

    return String(buffer);
  }

  String Context(String ctx) {
    char buffer[50];
    char fmt[25] = " | context:'%s'";

    sprintf(buffer, fmt, ctx.c_str());

    return String(buffer);
  }

  String FloatToString(float temperature) {
    char buffer[10];
    dtostrf(temperature, 6, 2, buffer);

    return String(buffer);
  }

  String Temperature(float temperature) {
    char buffer[50];
    char fmt[25] = " | temperature:'%s'";

    sprintf(buffer, fmt, FloatToString(temperature).c_str());

    return String(buffer);
  }
};
// DEBUG LOGGING ---------------------------------------------------------------
struct Debug {

  void LogCtxAndTemperature(DateTime now, String ctx, float temp) {
    fmt fmt;
    log(fmt.TimestampAndDate(now) + fmt.Context(ctx) + fmt.Temperature(temp));
  }

  void LogCtx(DateTime now, String ctx) {
    fmt fmt;
    log(fmt.TimestampAndDate(now) + fmt.Context(ctx));
  }

  void log(String msg) {

    if (DEBUG_LOG_OUTPUT & DEBUG_LOG_SERIAL) {
      LogSerial(msg);
    }
    if (DEBUG_LOG_OUTPUT & DEBUG_LOG_FILE) {
      LogFile(msg);
    }
  }
};

// TEMPERATURE -----------------------------------------------------------------
float GetTemperature() {
  // TEMPERATURE SENSOR STUB

  float temperature = 101.234;

  return temperature;
}

void WriteTemperature(float temperature) {
  // SD CARD WRITE STUB
}

// RTC -------------------------------------------------------------------------
void setupRTC() {
  if (!rtc.begin()) {
    error("RTC failed");
  }

  if (!rtc.initialized() || rtc.lostPower()) {
    Serial.println("RTC is not initialized... setting time");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  rtc.start();

  float drift = 43;
  float period_sec = (7 * 86400);
  float deviation_ppm = (drift / period_sec * 1000000);
  float drift_unit = 4.34;

  int offset = round(deviation_ppm / drift_unit);

  Serial.print("Offset is ");
  Serial.println(offset);
}

// SD --------------------------------------------------------------------------
void setupSD() {
  if (!SD.begin(10)) {
    error("Card failed, or not present");
  }
  Serial.println("SD initialized");

  char filename[] = "LOGS.CSV";
  if (!SD.exists(filename)) {
    logfile = SD.open(filename, FILE_WRITE);
  }

  if (!logfile) {
    error("couldnt create file");
  }
}

// SETUP -----------------------------------------------------------------------
void setup(void) {
  pinMode(NOTIFY_LED, OUTPUT);
  pinMode(10, OUTPUT);

  setupRTC();
  // setupSD();

  DEBUG_LOG_OUTPUT = DEBUG_LOG_SERIAL;
}

// LOOP ------------------------------------------------------------------------
void loop(void) {
  Serial.begin(57600);
  Debug debug;

  float temperature = GetTemperature();

  debug.LogCtxAndTemperature(rtc.now(), "took temp", temperature);

  WriteTemperature(temperature);

  debug.LogCtxAndTemperature(rtc.now(), "wrote temp to SD card", temperature);

  // NotifyWrite();

  delay(5 * SECOND);
}
