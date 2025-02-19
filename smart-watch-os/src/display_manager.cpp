#include "display_manager.h"

display_manager::display_manager(uint8_t width, uint8_t height, TwoWire& Wire,
                                 DFRobot_I2C_Multiplexer* Mux_main, int port)
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET),
      Mux(Mux_main),
      port_dis_man(port_dis_man) {}

void display_manager::begin() {
  Mux->selectPort(port_dis_man);

  while (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
  }

  Serial.println("Display initialized");

  display.display();
  delay(2000);

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  String message = "Hello, User";
  int16_t x = (SCREEN_WIDTH - (6 * message.length())) / 2;
  int16_t y = (SCREEN_HEIGHT - 8) / 2;
  display.setCursor(x, y);

  display.print(message);

  display.display();
}

void display_manager::clear() {
  Mux->selectPort(port_dis_man);
  display.clearDisplay();
}

void display_manager::draw_graph(int* graph_data) {
  Mux->selectPort(port_dis_man);

  for (int i = 0; i < SCREEN_WIDTH - 1; i++) {
    int y1 =
        map(graph_data[i], 0, 1023, SCREEN_HEIGHT - 1 - MARGIN, 0 + MARGIN);
    int y2 =
        map(graph_data[i + 1], 0, 1023, SCREEN_HEIGHT - 1 - MARGIN, 0 + MARGIN);

    display.drawLine(i, y1, i + 1, y2, WHITE);
  }
}

void display_manager::print_info(unsigned long time, int value) {
  Mux->selectPort(port_dis_man);

  display.setCursor(0, SCREEN_HEIGHT - 10);
  display.setTextColor(WHITE);
  display.print("Time: ");
  display.print(time / 1000);
  display.print("s ");
  display.print("Value: ");
  display.print(value);
}

void display_manager::update() {
  Mux->selectPort(port_dis_man);
  display.display();
}

void display_manager::need_help() {
  Mux->selectPort(port_dis_man);

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);

  String message = "NEED HELP!";
  int16_t x = (SCREEN_WIDTH - (6 * message.length())) / 2;
  int16_t y = (SCREEN_HEIGHT - 8) / 2;
  display.setCursor(x, y);

  display.print(message);

  display.display();
}
