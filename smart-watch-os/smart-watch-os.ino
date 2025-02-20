# include "src/scripts.h"

gyro_acc *gyroscope_accelerometer;
display_manager *oled;
graph_plotter graph;
shield *myShield;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);

  while (!Serial) blink();

  Serial.println(F("Hello World!"));

  Mux = new DFRobot_I2C_Multiplexer(&Wire, 0x70);
  Mux->begin();
  delay(1000);

  mux_scan(Mux);

  gyroscope_accelerometer = new gyro_acc();

  gyroscope_accelerometer->begin_fall_detector(port_fall_sensor);

  gyroscope_accelerometer->begin_pedometer(port_pedometer);

  oled = new display_manager(SCREEN_WIDTH, SCREEN_HEIGHT, Wire);

  oled->begin(port_oled_1);
  oled->begin(port_oled_2);
  oled->begin(port_oled_3);

  myShield = new shield(port_shield);

  myShield->get_time();
}

int num_loops = 0;

bool fallen = false;

void loop() {
  num_loops++;
  fallen = gyroscope_accelerometer->has_fallen(port_fall_sensor);

  if (fallen) {
    begin_countdown(gyroscope_accelerometer, oled);
  }

  if (num_loops > 1000) {
    num_loops = 0;
    gyroscope_accelerometer->count_steps(port_pedometer);
  }
}

