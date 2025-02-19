#pragma once

#include <Arduino.h>

#include "display_manager.h"

class graph_plotter {
 private:
  int graph_data[SCREEN_WIDTH];
  unsigned long previous_millis;
  const long refresh_interval;

 public:
  graph_plotter(long refresh_interval = 100);
  void preprocess_data(int input);
  void update_display(display_manager& display, unsigned long current_millis);
};