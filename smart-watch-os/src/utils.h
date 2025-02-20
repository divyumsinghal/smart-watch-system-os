#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <ArduinoSound.h>
#include <DFRobot_I2C_Multiplexer.h>
#include <LSM6DS3.h>
#include <RTClib.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
// #include <TMRpcm.h>

#define CLEAR_STEP true
#define NOT_CLEAR_STEP false

#define OLED_RESET -1

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define MARGIN 3
#define SCREEN_ADDRESS 0x3C

#define ACCELERATION_THRESHOLD 2.5
#define CONSCIOUSNESS_CHECK_TIME 30000

#define port_fall_sensor 0
#define port_oled_1 1
#define port_oled_2 2
#define port_oled_3 3
#define port_pedometer 4
#define port_shield 5

#define SD_ChipSelectPin 6
#define PWMIN 2

extern DFRobot_I2C_Multiplexer *Mux;

enum class UserState { state_fallen, state_not_fallen, state_countdown };
