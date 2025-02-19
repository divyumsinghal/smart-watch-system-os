#pragma once

#include <Arduino.h>
#include <LSM6DS3.h>
#include <Wire.h>
#include <DFRobot_I2C_Multiplexer.h>
#include "utils.h"


class fall_detector {
 private:
  LSM6DS3 lsm6ds3;
  DFRobot_I2C_Multiplexer* Mux;
  int port_fall_detector;

  int config_free_fall_detect();

 public:
  fall_detector(DFRobot_I2C_Multiplexer * Mux_main, int port);
  ~fall_detector();
  bool has_fallen();
  bool now_moving();

};
