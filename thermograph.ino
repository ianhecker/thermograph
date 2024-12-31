#include <RTClib.h>
#include <SD.h>
#include <SPI.h>

#define MILLISECOND 1
#define SECOND 1000 * MILLISECOND
#define MINUTE 60 * SECOND

#define DEBUG 1

#define CHIP_SELECT_PIN 10
#define TEMPERATURE_PIN 0

RTC_PCF8523 rtc;

char DAYS_OF_THE_WEEK[7][12] = {"Sunday",   "Monday", "Tuesday", "Wednesday",
                                "Thursday", "Friday", "Saturday"};

void error(char *err) {
  Serial.print("error: ");
  Serial.println(err);
  Serial.flush();
  while (1)
    delay(10);
}

String formatUnixTimestamp(DateTime dt) {
  //
  return String(dt.unixtime());
}

String formatHumanReadableTimestamp(DateTime dt) {
  char buffer[150];
  char fmt[50] = "%d/%02d/%02d %s %02d:%02d:%02d";

  char *dayOfTheWeek = DAYS_OF_THE_WEEK[dt.dayOfTheWeek()];

  sprintf(buffer, fmt, dt.year(), dt.month(), dt.day(), dayOfTheWeek, dt.hour(),
          dt.minute(), dt.second());

  return String(buffer);
}

String formatTemperature(float temperature) {
  char buffer[10];
  dtostrf(temperature, 0, 3, buffer);

  return String(buffer);
}

float getTemperature() {
  int reading = analogRead(TEMPERATURE_PIN);

  float voltage = (reading * 5.0) / 1105.0;
  float celsius = (voltage - 0.5) * 100.0;
  float fahrenheit = (celsius * 9.0 / 5.0) + 32.0;

  return fahrenheit;
}

void setup() {
  Serial.begin(9600);

  Serial.println("Initializing SD");

  if (!SD.begin(CHIP_SELECT_PIN)) {
    error("Initialization for SD failed");
  }
  Serial.println("Initialization for SD done");

  if (!rtc.begin()) {
    error("Initialization for RTC failed");
  }

  if (!rtc.initialized() || rtc.lostPower()) {
    Serial.println("RTC is not initialized... setting time");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  rtc.start();

  // Dummy reading to warm up
  getTemperature();
}

void loop() {
  File myFile = SD.open("LOGS.CSV", FILE_WRITE);

  if (myFile) {
    float temperature = getTemperature();

    DateTime now = rtc.now();

    String unixTime = formatUnixTimestamp(now);
    String humanTime = formatHumanReadableTimestamp(now);
    String tempString = formatTemperature(temperature);

    String rowInCSV =
        "'" + unixTime + "','" + humanTime + "','" + tempString + "F'";

    myFile.println(rowInCSV);
    myFile.flush();
    myFile.close();

    Serial.println(rowInCSV);
  } else {
    Serial.println("error opening file: LOGS.CSV");
  }

  delay(5 * MINUTE);
}
