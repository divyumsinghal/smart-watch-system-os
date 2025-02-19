#include "fall_detector.h"

// Constructor and Destructor

fall_detector::fall_detector(DFRobot_I2C_Multiplexer * Mux_main) : Mux(Mux_main) {
  Serial.println("Setup the fall detector");

  delay(100);

  if (lsm6ds3.begin() != 0) {
    Serial.println("fall_detector -> Failed to initialize LSM6DS3 sensor!");
  } else {
    Serial.println("fall_detector -> LSM6DS3 sensor initialized successfully.");
  }

  if (config_free_fall_detect() != 0) {
    Serial.println("Fail to configure!");
  } else {
    Serial.println("Success to Configure!");
  }
}

fall_detector::~fall_detector() {
  Serial.println("Shutting down fall_detector.");
}

// Public functions

bool fall_detector::has_fallen(void) {
  uint8_t readDataByte = 0;

  lsm6ds3.readRegister(&readDataByte, LSM6DS3_ACC_GYRO_WAKE_UP_SRC);

  readDataByte &= 0x20;
  if (readDataByte) {
    Serial.print("Free fall detected!  ");
  }

  return readDataByte;
}

// Private functions

int fall_detector::config_free_fall_detect(void) {
  uint8_t error = 0;
  uint8_t dataToWrite = 0;

  dataToWrite |= LSM6DS3_ACC_GYRO_BW_XL_200Hz;
  dataToWrite |= LSM6DS3_ACC_GYRO_FS_XL_2g;
  dataToWrite |= LSM6DS3_ACC_GYRO_ODR_XL_416Hz;

  error += lsm6ds3.writeRegister(LSM6DS3_ACC_GYRO_CTRL1_XL, dataToWrite);
  error += lsm6ds3.writeRegister(LSM6DS3_ACC_GYRO_WAKE_UP_DUR, 0x00);
  error += lsm6ds3.writeRegister(LSM6DS3_ACC_GYRO_FREE_FALL, 0x33);
  error += lsm6ds3.writeRegister(LSM6DS3_ACC_GYRO_MD1_CFG, 0x10);
  error += lsm6ds3.writeRegister(LSM6DS3_ACC_GYRO_MD2_CFG, 0x10);
  error += lsm6ds3.writeRegister(LSM6DS3_ACC_GYRO_TAP_CFG1, 0x81);

  return error;
}