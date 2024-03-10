#include "../config/PinDefs.h"
#include "../models/State.h"
#include <AceRoutine.h>
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#ifndef LightRods_h
#define LightRods_h

#define LIGHTS_PATTERN_RADAR 1
#define NEOPIXEL_COUNT 28

class LightRods : public ace_routine::Coroutine {
private:
  Adafruit_NeoPixel neopixels;
  State *state;

  uint8_t routine;
  uint8_t routineVariation;
  uint8_t i;

  void off();
  uint32_t getColor(uint8_t r, uint8_t g, uint8_t b);

public:
  LightRods(State *statePtr);

  void begin();
  int runCoroutine() override;

  void showPattern(uint8_t routine, uint8_t variation, bool restart = false);
  void clear();
};

#endif