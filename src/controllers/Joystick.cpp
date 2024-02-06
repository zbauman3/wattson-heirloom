#include "./Joystick.h"

Joystick::Joystick(State *statePtr) { this->state = statePtr; }

void Joystick::sample() {
  unsigned int lr = 0;
  unsigned int ud = 0;

  for (int i = 0; i < 16; i++) {
    lr += analogRead(PinDefs::joystickLR);
    ud += analogRead(PinDefs::joystickUD);
  }

  // shift 4 to get an average of 16. Then shift 4 more to reduce resolution and
  // get a stable 8 bit value
  this->state->joystick_lr = (unsigned char)(lr >> 8);
  this->state->joystick_ud = (unsigned char)(ud >> 8);
}

void Joystick::begin() {
  analogReadResolution(12);
  pinMode(PinDefs::joystickLR, INPUT);
  pinMode(PinDefs::joystickUD, INPUT);
}