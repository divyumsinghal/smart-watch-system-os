#include "src/fall_detector.h"
#include "src/display_manager.h"
#include "src/graph_plotter.h"

fall_detector *fall_sensor;
DFRobot_I2C_Multiplexer *Mux;
display_manager *oled_1;  // Status
display_manager *oled_2;  // Heartrate EKG
graph_plotter graph;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);

  while (!Serial) blink();

  Serial.println("Hello World!");

  Mux = new DFRobot_I2C_Multiplexer(&Wire, 0x70);
  Mux->begin();
  delay(1000);

  mux_scan(Mux);

  fall_sensor = new fall_detector(Mux, port_fall_sensor);

  oled_1 =
      new display_manager(SCREEN_WIDTH, SCREEN_HEIGHT, Wire, Mux, port_oled_1);
  oled_1->begin();

  oled_2 =
      new display_manager(SCREEN_WIDTH, SCREEN_HEIGHT, Wire, Mux, port_oled_2);
  oled_2->begin();
}

bool fallen = false;
bool all_ok = true;

void loop() {
  fallen = fall_sensor->has_fallen();

  if (fallen) {
    begin_countdown(fall_sensor, oled_1);
  }
}

void begin_countdown(fall_detector *myIMU, display_manager *myOLED) {
  unsigned long start_time = millis();
  unsigned long current_time = millis();
  unsigned long elapsed_time = 0;

  while (elapsed_time < CONSCIOUSNESS_CHECK_TIME) {
    current_time = millis();
    elapsed_time = current_time - start_time;

    if (myIMU->now_moving()) return;
  }

  myOLED->need_help();



}