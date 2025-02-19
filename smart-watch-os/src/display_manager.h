#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <DFRobot_I2C_Multiplexer.h>
#include <SPI.h>
#include <Wire.h>

#include "utils.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define MARGIN 3
#define SCREEN_ADDRESS 0x3C

class display_manager {
 private:
  Adafruit_SSD1306 display;
  DFRobot_I2C_Multiplexer *Mux;
  int port_dis_man;

 public:
  display_manager(uint8_t width, uint8_t height, TwoWire &Wire,
                  DFRobot_I2C_Multiplexer *Mux_main, int port);
  void begin();
  void clear();
  void draw_graph(int *graph_data);
  void print_info(unsigned long time, int value);
  void update();
  void need_help();
};
