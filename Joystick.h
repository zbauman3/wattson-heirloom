#include <Arduino.h>

#ifndef Joystick_H
#define Joystick_H

typedef struct {
  unsigned char lr;
  unsigned char ud;
} joystickValues;

// this expects the analogReadResolution to be `8`
class Joystick {
private:
  unsigned char lr;
  unsigned char ud;

public:
  Joystick(unsigned char lrPin, unsigned char udPin);

  joystickValues sample();
  void begin();
};

#endif