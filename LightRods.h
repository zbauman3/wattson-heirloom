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
  // 1: 1 quick flash
  unsigned char routine;

  void off();

public:
  LightRods();

  void begin();
  int runCoroutine() override;

  void tmp_flash();
};

#endif