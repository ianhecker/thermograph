#include "logger.h"

Logger logger;

void setup() {
  logger.begin(9600);
  logger.setLogLevel(LOG_LEVEL_INFO);

  uint32_t currentUnixTime = 1700000000;
  float currentTemperature = 23.5;

  logger.logInfo(currentUnixTime, currentTemperature, "System initialized");
  logger.logError(currentUnixTime, "Temperature sensor failure detected");
}

void loop() {
  static uint32_t timestamp = 1700000000;
  static float temperature = 25.0;

  logger.logInfo(timestamp, temperature, "System operational");
  delay(5000);
  timestamp += 5;
  temperature += 0.1;
}
