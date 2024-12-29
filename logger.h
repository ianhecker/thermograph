#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

enum LogLevel { LOG_LEVEL_INFO, LOG_LEVEL_ERROR };

class Logger {
public:
  Logger();
  void begin(int baudRate);
  void setLogLevel(LogLevel level);
  void log(LogLevel level, uint32_t timestamp, float temperature,
           const char *message);
  void logInfo(uint32_t timestamp, float temperature, const char *message);
  void logError(uint32_t timestamp, const char *message);

private:
  LogLevel currentLogLevel;
};

#endif
