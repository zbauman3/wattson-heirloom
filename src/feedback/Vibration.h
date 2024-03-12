#include "../config/PinDefs.h"
#include "./LightRods.h"
#include <AceRoutine.h>
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#ifndef Vibration_H
#define Vibration_H

#define VIBE_PATTERN_TRIGGER_INIT 3
#define VIBE_PATTERN_TRIGGER_BUILD 4
#define VIBE_PATTERN_TRIGGER_HIGHPOWER 5
#define VIBE_PATTERN_TRIGGER_LOWPOWER 6

class Vibration : public ace_routine::Coroutine {
private:
  // 0: off
  // 1: trigger - quick
  uint8_t routine;
  uint8_t i, j, k;

  void set(uint8_t value, bool allowDeadzone = false);
  bool changeRoutine(uint8_t routine, bool restart);

public:
  Vibration();

  int runCoroutine() override;
  void begin();
  void clear();
  void triggerInit();
  void triggerBuild();
  void triggerHighPower();
  void triggerLowPower();
};

#endif