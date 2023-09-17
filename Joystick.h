#include "./PinDefs.h"
#include <Arduino.h>

#ifndef Joystick_H
#define Joystick_H

#define NUM_SAMPLES 255

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