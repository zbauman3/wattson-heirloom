#include <Arduino.h>

#ifndef Z_Joystick_H
#define Z_Joystick_H

typedef struct {
  unsigned char lr;
  unsigned char ud;
} joystickValues;

// this expects the analogReadResolution to be `8`
class Z_Joystick {
private:
  unsigned char lr;
  unsigned char ud;

public:
  Z_Joystick(unsigned char lrPin, unsigned char udPin);

  joystickValues sample();
  void begin();
};

#endif