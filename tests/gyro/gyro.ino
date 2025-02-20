#include "../../smart-watch-os/src/gyro_acc.h"

gyro_acc *gyroscope_accelerometer;

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

  gyroscope_accelerometer = new gyro_acc(0);
}

bool fallen = false;

void loop() { fallen = gyroscope_accelerometer->has_fallen(0); }