#include "gyro_acc.h"

// Constructor and Destructor

gyro_acc::gyro_acc() {}

// Public functions

void gyro_acc::begin_fall_detector(int port_fall_detector) {
  Serial.println(F("Setup the fall detector"));

  Mux->selectPort(port_fall_detector);

  delay(100);

  if (lsm6ds3.begin() != 0) {
    Serial.println(F("fall_detector -> Failed to initialize LSM6DS3 sensor!"));
  } else {
    Serial.println(F("fall_detector -> LSM6DS3 sensor initialized successfully."));
  }

  if (config_free_fall_detect(port_fall_detector) != 0) {
    Serial.println(F("Fail to configure!"));
  } else {
    Serial.println(F("Success to Configure!"));
  }
}

bool gyro_acc::has_fallen(int port_fall_detector) {
  Mux->selectPort(port_fall_detector);

  uint8_t readDataByte = 0;

  lsm6ds3.readRegister(&readDataByte, LSM6DS3_ACC_GYRO_WAKE_UP_SRC);

  readDataByte &= 0x20;
  if (readDataByte) {
    Serial.print("Free fall detected!  ");
  }

  return readDataByte;
}

bool gyro_acc::now_moving(int port_fall_detector) {
  Mux->selectPort(port_fall_detector);

  uint16_t aX, aY, aZ, aSum;

  aX = fabs(lsm6ds3.readFloatAccelX());
  aY = fabs(lsm6ds3.readFloatAccelY());
  aZ = fabs(lsm6ds3.readFloatAccelZ());

  aSum = fabs(aX) + fabs(aY) + fabs(aZ);

  return (aSum >= ACCELERATION_THRESHOLD);
}

void gyro_acc::begin_pedometer(int port_ped) {
  Serial.println(F("Setup the pedometer"));

  Mux->selectPort(port_ped);

  delay(100);

  if (lsm6ds3.begin() != 0) {
    Serial.println(F("pedometer -> Failed to initialize LSM6DS3 sensor!"));
  } else {
    Serial.println(F("pedometer -> LSM6DS3 sensor initialized successfully."));
  }

  if (config_pedometer(NOT_CLEAR_STEP, port_ped) != 0) {
    Serial.println(F("Configure pedometer fail!"));
  } else {
    Serial.println(F("Success to Configure pedometer!"));
  }
  dataByte = 0;
  stepCount = 0;
}

void gyro_acc::count_steps(int port_ped) {
  Mux->selectPort(port_ped);

  lsm6ds3.readRegister(&dataByte, LSM6DS3_ACC_GYRO_STEP_COUNTER_H);
  stepCount = (dataByte << 8) & 0xFFFF;

  lsm6ds3.readRegister(&dataByte, LSM6DS3_ACC_GYRO_STEP_COUNTER_L);
  stepCount |= dataByte;

  Serial.print("Step: ");
  Serial.println(stepCount);
}

// Private functions

int gyro_acc::config_free_fall_detect(int port_fall_detector) {
  Mux->selectPort(port_fall_detector);

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

int gyro_acc::config_pedometer(bool clearStep, int port_ped) {
  Mux->selectPort(port_ped);

  uint8_t errorAccumulator = 0;
  uint8_t dataToWrite = 0;  // Temporary variable

  // Setup the accelerometer******************************
  dataToWrite = 0;

  //  dataToWrite |= LSM6DS3_ACC_GYRO_BW_XL_200Hz;
  dataToWrite |= LSM6DS3_ACC_GYRO_FS_XL_2g;
  dataToWrite |= LSM6DS3_ACC_GYRO_ODR_XL_26Hz;

  // Step 1: Configure ODR-26Hz and FS-2g
  errorAccumulator +=
      lsm6ds3.writeRegister(LSM6DS3_ACC_GYRO_CTRL1_XL, dataToWrite);

  // Step 2: Set bit Zen_G, Yen_G, Xen_G, FUNC_EN, PEDO_RST_STEP(1 or 0)
  if (clearStep) {
    errorAccumulator += lsm6ds3.writeRegister(LSM6DS3_ACC_GYRO_CTRL10_C, 0x3E);
  } else {
    errorAccumulator += lsm6ds3.writeRegister(LSM6DS3_ACC_GYRO_CTRL10_C, 0x3C);
  }

  // Step 3:	Enable pedometer algorithm
  errorAccumulator += lsm6ds3.writeRegister(LSM6DS3_ACC_GYRO_TAP_CFG1, 0x40);

  // Step 4:	Step Detector interrupt driven to INT1 pin, set bit
  // INT1_FIFO_OVR
  errorAccumulator += lsm6ds3.writeRegister(LSM6DS3_ACC_GYRO_INT1_CTRL, 0x10);

  return errorAccumulator;
}
