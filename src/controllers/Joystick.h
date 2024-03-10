#include "../config/PinDefs.h"
#include "../models/State.h"
#include <AceRoutine.h>
#include <Arduino.h>

#ifndef Joystick_H
#define Joystick_H

// this expects the analogReadResolution to be `8`
class Joystick : public ace_routine::Coroutine {
private:
  State *state;

public:
  Joystick(State *statePtr);

  void sample();
  void begin();

  int runCoroutine() override;
};

#endif