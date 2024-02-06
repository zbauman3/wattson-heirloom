#include "./Rotary.h"

#define ROTARY_SWITCH 24
#define ROTARY_ADDR 0x36

Rotary::Rotary(State *statePtr) : ss(Adafruit_seesaw()) {
  this->state = statePtr;
}

bool Rotary::begin() {
  if (!this->ss.begin(ROTARY_ADDR)) {
    DEBUG_LN("Couldn't find seesaw on default address.");
    return false;
  }

  unsigned long version = ((this->ss.getVersion() >> 16) & 0xFFFF);
  if (version != 4991) {
    DEBUG_F("Wrong seesaw firmware loaded? %d\n", version);
    return false;
  }

  // trigger state updates
  this->getValue();
  this->isPressed();

  return true;
}

void Rotary::enableInterrupts() {
  this->ss.setGPIOInterrupts((uint32_t)1 << ROTARY_SWITCH, 1);
  this->ss.enableEncoderInterrupt();
}

signed long Rotary::getValue() {
  signed long pos = this->ss.getEncoderPosition();
  this->state->rotary_position = pos;
  return this->state->rotary_position;
}

bool Rotary::isPressed() {
  bool btn = this->ss.digitalRead(ROTARY_SWITCH);
  this->state->rotary_btn = !btn;
  return this->state->rotary_btn;
}