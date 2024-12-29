#include "logger.h"

Logger::Logger() : currentLogLevel(LOG_LEVEL_INFO) {}

void Logger::begin(int baudRate) {
  Serial.begin(baudRate);
  while (!Serial) {
  }
}

void Logger::setLogLevel(LogLevel level) { currentLogLevel = level; }

void Logger::log(LogLevel level, uint32_t timestamp, float temperature,
                 const char *message) {
  if (level >= currentLogLevel) {
    char buffer[128];
    char tempBuffer[16];

    // Convert temperature to string without padding
    dtostrf(temperature, 0, 2, tempBuffer);

    const char *levelStr = (level == LOG_LEVEL_INFO) ? "INFO" : "ERROR";

    // Format the message
    sprintf(buffer, "[%lu] [%s] [TEMPERATURE:%s°F] [CONTEXT:%s]", timestamp,
            levelStr, tempBuffer, message);
    Serial.println(buffer);
  }
}

void Logger::logInfo(uint32_t timestamp, float temperature,
                     const char *message) {
  log(LOG_LEVEL_INFO, timestamp, temperature, message);
}

void Logger::logError(uint32_t timestamp, const char *message) {
  log(LOG_LEVEL_ERROR, timestamp, 0.0, message);
}
