#include "./PinDefs.h"
#include <Arduino.h>

#ifndef Joystick_H
#define Joystick_H

typedef struct {
  unsigned char lr;
  unsigned char ud;
} joystickValues;

// this expects the analogReadResolution to be `8`
class Joystick {
public:
  joystickValues sample();
  void begin();
};

#endif