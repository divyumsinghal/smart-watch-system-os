#pragma once

#include <Arduino.h>
#include <LSM6DS3.h>
#include <Wire.h>
#include <DFRobot_I2C_Multiplexer.h>

class fall_detector {
 private:
  LSM6DS3 lsm6ds3;
  DFRobot_I2C_Multiplexer* Mux;


  int config_free_fall_detect();

 public:
  fall_detector();
  ~fall_detector();
  bool has_fallen();
};
