#pragma once

#include "utils.h"
#include "display_manager.h"

class graph_plotter {
 private:
  alignas(4) uint8_t graph_data[SCREEN_WIDTH];
  const unsigned long refresh_interval;  // Move this above 'previous_millis'
  unsigned long previous_millis;

 public:
  graph_plotter(long refresh_interval = 100);
  void preprocess_data(uint8_t input);
  void update_display(display_manager& display, unsigned long current_millis);
};
