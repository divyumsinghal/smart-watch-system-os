#include "shield.h"

// Constructor & Destructor

shield::shield(int port)
    : port_clock(port){
  Mux->selectPort(port_clock);

  init_clock();
  init_SD();
}

// Private

void shield::init_clock() {
  Mux->selectPort(port_clock);

#ifndef ESP8266
  while (!Serial);
#endif

  if (!rtc.begin()) {
    Serial.println(F("Couldn't find RTC"));
    Serial.flush();
    // while (1) delay(10);
  }

  if (!rtc.initialized() || rtc.lostPower()) {
    Serial.println(F("RTC is NOT initialized, let's set the time!"));
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  rtc.start();
}

void shield::init_SD() {
  // tmrpcm.speakerPin = 9;

  pinMode(PWMIN, INPUT);

  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println(F("SD fail"));
    return;
  } else if (SD.begin(SD_ChipSelectPin)) {
    Serial.println(F("SD connected"));
    // tmrpcm.play("Setup.wav");
    // tmrpcm.volume(5);
    // delay(15000);
    // tmrpcm.volume(0);

    waveFile = SDWaveFile("MUSIC.WAV");
    AudioOutI2S.volume(5);

    AudioOutI2S.play(waveFile);

    while (!AudioOutI2S.isPlaying());
  }
}

// Public

void shield::get_time() {
  Mux->selectPort(port_clock);

  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print(':');
  Serial.print(now.month(), DEC);
  Serial.print(':');
  Serial.print(now.day(), DEC);
  Serial.print(':');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
}

void shield::play_wav(String wav_name) {
  // tmrpcm.play(wav_name.c_str());
  // tmrpcm.volume(5);

  waveFile = SDWaveFile(wav_name.c_str());
  AudioOutI2S.volume(5);

  AudioOutI2S.play(waveFile);

  while (!AudioOutI2S.isPlaying());
}
