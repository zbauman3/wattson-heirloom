#include "./Joystick.h"

Joystick::Joystick(State *statePtr) { this->state = statePtr; }

void Joystick::sample() {
  uint16_t lr = 0;
  uint16_t ud = 0;

  for (int i = 0; i < 16; i++) {
    lr += analogRead(PinDefs::joystickLR);
    ud += analogRead(PinDefs::joystickUD);
  }

  // shift 4 to get an average of 16. Then shift 4 more to reduce resolution and
  // get a stable 8 bit value
  this->state->setJoystick((uint8_t)(lr >> 8), (uint8_t)(ud >> 8));
}

void Joystick::begin() {
  analogReadResolution(12);
  pinMode(PinDefs::joystickLR, INPUT);
  pinMode(PinDefs::joystickUD, INPUT);
}

int Joystick::runCoroutine() {
  COROUTINE_LOOP() {
    this->sample();

    if (this->state->joystickMoving()) {
      COROUTINE_YIELD();
    } else {
      COROUTINE_DELAY(500);
    }
  }
}