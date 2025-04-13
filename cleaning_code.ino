#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

int Relay = 4;

const int OnHour = 2;     // Set relay ON time (24-hour format)
const int OnMin = 35;
const int OffHour = 2;    // Set relay OFF time
const int OffMin = 36;

void setup() {
  Serial.begin(115200);
  rtc.begin();

  // Uncomment the following line ONLY ONCE to set RTC to current PC time:
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, HIGH); // Start OFF (HIGH = inactive)
}

void loop() {
  DateTime now = rtc.now();

  Serial.print(now.hour());
  Serial.print(" hour(s), ");
  Serial.print(now.minute());
  Serial.println(" minute(s)");

  if (now.hour() == OnHour && now.minute() == OnMin) {
    digitalWrite(Relay, LOW); // Relay ON (active LOW)
    Serial.println("RELAY ON");
  }

  if (now.hour() == OffHour && now.minute() == OffMin) {
    digitalWrite(Relay, HIGH); // Relay OFF
    Serial.println("RELAY OFF");
  }

  delay(1000);
}
