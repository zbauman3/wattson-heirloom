#include "./Macros.h"
#include "./State.h"
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
  signed long getValue();
  bool isPressed();
};

#endif