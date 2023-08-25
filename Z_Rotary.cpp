#include "Z_Rotary.h"
#include "Adafruit_seesaw.h"
#include "Z_Macros.h"
#include <Arduino.h>

Z_Rotary::Z_Rotary(unsigned int addr) : ss(Adafruit_seesaw()) {
  this->addr = addr;
}

bool Z_Rotary::begin() {
  if (!this->ss.begin(this->addr)) {
    DEBUG_LN("Couldn't find seesaw on default address.");
    return false;
  }

  unsigned long version = ((this->ss.getVersion() >> 16) & 0xFFFF);
  if (version != 4991) {
    DEBUG_F("Wrong seesaw firmware loaded? %d\n", version);
    return false;
  }

  return true;
}

signed long Z_Rotary::getValue() { return this->ss.getEncoderPosition(); }