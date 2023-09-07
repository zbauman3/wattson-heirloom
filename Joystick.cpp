#include "./Joystick.h"
#include <Arduino.h>

// this expects the analogReadResolution to be `8`
Joystick::Joystick(unsigned char lrPin, unsigned char udPin) {
  this->lr = lrPin;
  this->ud = udPin;
}

joystickValues Joystick::sample() {
  int lr = 0;
  int ud = 0;

  for (int i = 0; i < NUM_SAMPLES; i++) {
    lr += analogRead(this->lr);
    ud += analogRead(this->ud);
  }

  return {.lr = (unsigned char)(lr / NUM_SAMPLES),
          .ud = (unsigned char)(ud / NUM_SAMPLES)};
}

void Joystick::begin() {
  pinMode(this->lr, INPUT);
  pinMode(this->ud, INPUT);
}