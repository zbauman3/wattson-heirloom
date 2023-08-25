
#include "Adafruit_seesaw.h"
#include "Z_Macros.h"
#include <Arduino.h>

#ifndef Z_Rotary_H
#define Z_Rotary_H

class Z_Rotary {
private:
  unsigned int addr;
  Adafruit_seesaw ss;

public:
  Z_Rotary(unsigned int addr);
  bool begin();
  signed long getValue();
};

#endif