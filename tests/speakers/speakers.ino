#include <SD.h>  // need to include the SD library
// Sd card wav file names must be under 8 charcters ie 12345678.wav
#include <SPI.h>     // need to include the SPI library
#include <TMRpcm.h>  //  Lib to play wav file

#define SD_ChipSelectPin 6  // using digital pin 6 for the SD card select pin
#define PWMIN 2             // using digital pin 2 for the audio signal input

TMRpcm tmrpcm;           // create an object for use in this sketch
unsigned long duration;  // variable to store the duration of the high side of
                         // the PWM signal

void setup() {
  tmrpcm.speakerPin =
      9;  // pin 9 for Aduino Pro Mini , any pin with PWM fonction will work too
  Serial.begin(9600);

  pinMode(PWMIN, INPUT);

  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be
                                      // initialized:
    Serial.println("SD fail");
    return;  // don't do anything more if not
  } else if (SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD connected");
    tmrpcm.play("Setup.wav");  // the sound file "Setup " will play each time
                               // the arduino powers up, or is reset
    tmrpcm.volume(5);
    delay(15000);
    tmrpcm.volume(0);
  }
}

void loop() {
  duration = pulseIn(
      PWMIN, HIGH);  // measure the duration of the high side of PWM Pin.
  Serial.println(duration);

  if (150 < duration && duration < 250)  // 25 PWM
  {
    tmrpcm.play("ID.wav");
    tmrpcm.volume(5);
    delay(4000);
    tmrpcm.volume(0);
  }
  if (370 < duration && duration < 410)  // 50 PWM
  {
    tmrpcm.play("ObjS.wav");
    tmrpcm.volume(5);
    delay(4000);
    tmrpcm.volume(0);
  }
  if (700 < duration && duration < 850)  // 100 PWM
  {
    tmrpcm.play("GUIS.wav");
    tmrpcm.volume(5);
    delay(4000);
    tmrpcm.volume(0);
  }
  if (1100 < duration && duration < 1250)  // 150 PWM
  {
    tmrpcm.play("SignS.wav");
    tmrpcm.volume(5);
    delay(4000);
    tmrpcm.volume(0);
  }
  if (1500 < duration && duration < 1650)  // 200 PWM
  {
    tmrpcm.play("SignR.wav");
    tmrpcm.volume(5);
    delay(4000);
    tmrpcm.volume(0);
  }
  if (1900 < duration && duration < 2050)  // 250 PWM
  {
    tmrpcm.play("SignL.wav");
    tmrpcm.volume(5);
    delay(4000);
    tmrpcm.volume(0);
  }
}