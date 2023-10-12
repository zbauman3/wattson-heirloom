#include "./PinDefs.h"
#include "./State.h"
#include <Arduino.h>

#ifndef Joystick_H
#define Joystick_H

// this expects the analogReadResolution to be `8`
class Joystick {
private:
  State *state;

public:
  Joystick(State *statePtr);

  void sample();
  void begin();
};

#endif