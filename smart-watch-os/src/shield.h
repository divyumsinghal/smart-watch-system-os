#pragma once

#include "utils.h"

class shield {
 private:
  RTC_PCF8523 rtc;
  int port_clock;
  DateTime newDT;
  // TMRpcm tmrpcm;
  void init_clock();
  void init_SD();
  SDWaveFile waveFile;


 public:
  shield(int port);

  void get_time();
  void play_wav(String wav_name);
};
