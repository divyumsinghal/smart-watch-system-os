#include "utils.h"
void blink() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

void mux_scan(DFRobot_I2C_Multiplexer *Mux) {
  Serial.println("Scan ready!");

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
