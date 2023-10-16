#include "./PinDefs.h"
#include <AceRoutine.h>
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#ifndef LightRods_h
#define LightRods_h

class LightRods : public ace_routine::Coroutine {
private:
  Adafruit_NeoPixel neopixels;

  // 0: off
  // 1: trigger - quick
  unsigned char routine;
  unsigned short int routineLoop;

  void off();

public:
  LightRods();

  void begin();
  int runCoroutine() override;

  void startPattern(unsigned char routine);
};

#endif