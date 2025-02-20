#pragma once

#include "utils.h"

class gyro_acc {
 private:
  LSM6DS3 lsm6ds3;
  uint8_t dataByte;
  uint16_t stepCount;

  int config_free_fall_detect(int port_fall_detector);
  int config_pedometer(bool clearStep, int port_ped);

 public:
  gyro_acc();

  void begin_fall_detector(int port_fall_detector);
  bool has_fallen(int port_fall_detector);
  bool now_moving(int port_fall_detector);

  void begin_pedometer(int port_ped);
  void count_steps(int port_ped);
};
