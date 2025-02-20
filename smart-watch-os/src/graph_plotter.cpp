#include "graph_plotter.h"

graph_plotter::graph_plotter(long refresh_interval)
    : refresh_interval(refresh_interval), previous_millis(0) {
  memset(graph_data, 0, sizeof(graph_data));
}


void graph_plotter::preprocess_data(uint8_t input) {
  for (int i = 0; i < SCREEN_WIDTH - 1; i++) {
    graph_data[i] = graph_data[i + 1];
  }
  graph_data[SCREEN_WIDTH - 1] = input;
}

void graph_plotter::update_display(display_manager& display,
                                   unsigned long current_millis) {
  if (current_millis - previous_millis >= refresh_interval) {
    previous_millis = current_millis;

    display.clear(port_oled_1);
    display.draw_graph(graph_data, port_oled_1);
    display.update(port_oled_1);
  }
}