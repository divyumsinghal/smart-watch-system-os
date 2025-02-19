#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <DFRobot_I2C_Multiplexer.h>

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


enum class UserState { state_fallen, state_not_fallen, state_countdown };

void blink();
void mux_scan(DFRobot_I2C_Multiplexer *Mux);