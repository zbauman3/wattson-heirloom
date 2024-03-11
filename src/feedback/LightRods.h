#include "../config/PinDefs.h"
#include "../models/State.h"
#include <AceRoutine.h>
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#ifndef LightRods_h
#define LightRods_h

#define LIGHTS_PATTERN_RADAR 1
#define LIGHTS_PATTERN_RAINBOW 2
#define NEOPIXEL_COUNT 28

class LightRods : public ace_routine::Coroutine {
private:
  Adafruit_NeoPixel neopixels;
  State *state;

  uint8_t routine;
  uint8_t routineVariation;
  uint8_t i;
  long rainbowHue;
  uint16_t rainbowSpeed;
  bool rainbowDirection;

  void off();
  uint32_t adjustColorByPower(uint8_t r, uint8_t g, uint8_t b, float percent);
  bool changeRoutine(uint8_t routine, bool restart);
  void showColor(uint8_t r, uint8_t g, uint8_t b);

public:
  LightRods(State *statePtr);

  void begin();
  int runCoroutine() override;
  void clear();

  void radarPulse(bool danger = false);
  void rainbow(uint8_t brightness, uint16_t speed, bool direction);
  void solid(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness,
             uint8_t portion = 2);

  static uint8_t adjustBrightness(uint8_t color, float percent);
  static float brightnessToPercent(uint8_t brightness);
};

#endif