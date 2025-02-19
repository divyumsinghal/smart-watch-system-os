#include "fall_detector.h"

fall_detector *fall_sensor;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);

  while (!Serial) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }

  Serial.println("Hello World!");
  Wire.begin();

  fall_sensor = new fall_detector();
}

bool fallen = false;

void loop() { fallen = fall_sensor->has_fallen(); }