#include "scripts.h"


void blink() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

void mux_scan(DFRobot_I2C_Multiplexer *Mux) {
  Serial.println(F("Scan ready!"));

  for (uint8_t port = 0; port < 8; port++) {
    Serial.print("Port:");
    Serial.print(port);
    uint8_t *dev = Mux->scan(port);
    while (*dev) {
      Serial.print("  i2c addr ");
      Serial.print(*dev);
      dev++;
    }
    Serial.println();
  }
}

void begin_countdown(gyro_acc *myIMU, display_manager *myOLED) {
  unsigned int start_time = millis();
  unsigned int current_time = millis();
  unsigned int elapsed_time = 0;

  while (elapsed_time < CONSCIOUSNESS_CHECK_TIME) {
    current_time = millis();
    elapsed_time = current_time - start_time;

    if (myIMU->now_moving(port_fall_sensor)) return;
  }

  myOLED->need_help(port_oled_2);
}
