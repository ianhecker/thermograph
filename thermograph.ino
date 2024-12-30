#include <RTClib.h>

struct Logger {
  void begin(int baudRate) {
    Serial.begin(baudRate);
    while (!Serial) {
    }
  }

  void debug(uint32_t timestamp, const char *context) {
    char buffer[100];
    sprintf(buffer, "[DEBUG] [timestamp:%lu] [context:%s]", timestamp, context);
    Serial.println(buffer);
  }

  void info(uint32_t timestamp, float temperature, const char *context) {
    char buffer[100];
    char fmt[100] = "[INFO] [timestamp:%lu] [temperature:%s°F] [context:%s]";

    char tempBuffer[16];
    dtostrf(temperature, 0, 2, tempBuffer);

    sprintf(buffer, fmt, timestamp, tempBuffer, context);
    Serial.println(buffer);
  }

  void error(uint32_t timestamp, const char *context) {
    char buffer[100];
    sprintf(buffer, "[ERROR] [timestamp:%lu] [context:%s]", timestamp, context);
    Serial.println(buffer);
  }
};

Logger logger;

RTC_PCF8523 rtc;

void error(Logger logger, uint32_t timestamp, char *context) {
  logger.error(timestamp, context);
  Serial.flush();
  while (1)
    delay(10);
}

void setupRTC(Logger logger) {
  if (!rtc.begin()) {
    error(logger, 0, "RTC failed");
  }

  if (!rtc.initialized() || rtc.lostPower()) {
    logger.debug(0, "RTC is not initialized... setting time");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  rtc.start();

  float drift = 43;
  float period_sec = (7 * 86400);
  float deviation_ppm = (drift / period_sec * 1000000);
  float drift_unit = 4.34;

  int offset = round(deviation_ppm / drift_unit);

  logger.debug(rtc.now().unixtime(), "RTC offset is: " + offset);
}

void setup() {
  logger.begin(9600);

  delay(5000);

  setupRTC(logger);

  logger.debug(rtc.now().unixtime(), "initialized rtc");
}

void loop() {

  uint32_t timestamp = rtc.now().unixtime();
  float temp = 68.4;

  logger.info(timestamp, temp, "measured temperature");

  delay(5000);
}
