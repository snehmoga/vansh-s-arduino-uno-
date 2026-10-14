
#include <Arduino.h>

// Pin configuration
const int LDR_PIN = A0;
const int LED_PIN = 8;

// Darkness threshold
const int DARKNESS_THRESHOLD = 70;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);

  Serial.println();
  Serial.println("================================");
  Serial.println("      SMART LED SYSTEM");
  Serial.println("================================");
  Serial.println("System initialized!");
  delay(1000);
}

void loop() {
  // Read LDR analog value
  int sensorValue = analogRead(LDR_PIN);

  // Estimate darkness percentage.
  // Assumes lower analog readings mean darker conditions.
  int darkness = map(sensorValue, 0, 1023, 100, 0);
  darkness = constrain(darkness, 0, 100);

  int lightLevel = 100 - darkness;

  // LED ON when darkness is below 70%
  bool ledOn = darkness < DARKNESS_THRESHOLD;

  digitalWrite(LED_PIN, ledOn ? HIGH : LOW);

  // Progress bar (20 characters)
  int filled = darkness / 5;

  // Display live readings
  Serial.println();
  Serial.println("========== SMART LED ==========");

  Serial.print("LDR Sensor : ");
  Serial.println(sensorValue);

  Serial.print("Light Level: ");
  Serial.print(lightLevel);
  Serial.println("%");

  Serial.print("Darkness    : ");
  Serial.print(darkness);
  Serial.println("%");

  Serial.print("Darkness    : [");

  for (int i = 0; i < 20; i++) {
    if (i < filled) {
      Serial.print("#");
    } else {
      Serial.print("-");
    }
  }

  Serial.println("]");

  Serial.print("Threshold   : ");
  Serial.print(DARKNESS_THRESHOLD);
  Serial.println("%");

  Serial.print("LED Status  : ");
  Serial.println(ledOn ? "ON" : "OFF");

  Serial.println("================================");

  delay(500);
}
