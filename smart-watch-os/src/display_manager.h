#pragma once

#include "utils.h"

class display_manager {
 private:
  Adafruit_SSD1306 display;
  int port_dis_man;

 public:
  display_manager(uint8_t width, uint8_t height, TwoWire &Wire);
  void begin(int port_dis_man);
  void clear(int port_dis_man);
  void draw_graph(uint8_t *graph_data, int port_dis_man);
  void print_info(unsigned long time, int value, int port_dis_man);
  void update(int port_dis_man);
  void need_help(int port_dis_man);
};
