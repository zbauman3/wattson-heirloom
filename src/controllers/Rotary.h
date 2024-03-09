#include "../config/Macros.h"
#include "../models/State.h"
#include "Adafruit_seesaw.h"
#include <Arduino.h>

#ifndef Rotary_H
#define Rotary_H

class Rotary {
private:
  Adafruit_seesaw ss;
  State *state;

public:
  Rotary(State *statePtr);
  bool begin();
  void enableInterrupts();
  int32_t getValue();
  bool isPressed();
};

#endif