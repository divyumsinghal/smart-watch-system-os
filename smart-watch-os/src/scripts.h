#include "utils.h"

// Here
#include "display_manager.h"
#include "gyro_acc.h"
#include "shield.h"
#include "wiring_private.h"

// depends
#include "graph_plotter.h"

void blink();
void mux_scan(DFRobot_I2C_Multiplexer *Mux);
void begin_countdown(gyro_acc *myIMU, display_manager *myOLED);