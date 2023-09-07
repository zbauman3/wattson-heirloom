#include "./Rotary.h"
#include "./Macros.h"
#include "Adafruit_seesaw.h"
#include <Arduino.h>

#define ROTARY_SWITCH 24

Rotary::Rotary(unsigned int addr) : ss(Adafruit_seesaw()) { this->addr = addr; }

bool Rotary::begin() {
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

void Rotary::enableInterrupts() {
  this->ss.setGPIOInterrupts((uint32_t)1 << ROTARY_SWITCH, 1);
  this->ss.enableEncoderInterrupt();
}

signed long Rotary::getValue() { return this->ss.getEncoderPosition(); }
bool Rotary::isPressed() { return this->ss.digitalRead(ROTARY_SWITCH) == LOW; }