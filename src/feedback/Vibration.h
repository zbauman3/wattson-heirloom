#include "../config/PinDefs.h"
#include <AceRoutine.h>
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#ifndef Vibration_H
#define Vibration_H

class Vibration : public ace_routine::Coroutine {
private:
  // 0: off
  // 1: trigger - quick
  uint8_t routine;

  void set(uint8_t value);

public:
  Vibration();

  int runCoroutine() override;
  void begin();

  void startPattern(uint8_t which);
};

#endif