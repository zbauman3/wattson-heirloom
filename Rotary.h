
#include "./Macros.h"
#include "Adafruit_seesaw.h"
#include <Arduino.h>

#ifndef Rotary_H
#define Rotary_H

class Rotary {
private:
  unsigned int addr;
  Adafruit_seesaw ss;

public:
  Rotary(unsigned int addr);
  bool begin();
  void enableInterrupts();
  signed long getValue();
  unsigned char getButton();
};

#endif