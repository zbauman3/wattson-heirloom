#include "./Joystick.h"
#include <Arduino.h>

// this expects the analogReadResolution to be `8`
Z_Joystick::Z_Joystick(unsigned char lrPin, unsigned char udPin) {
  this->lr = lrPin;
  this->ud = udPin;
}

joystickValues Z_Joystick::sample() {
  int lr = 0;
  int ud = 0;

  for (int i = 0; i < 255; i++) {
    lr += analogRead(this->lr);
    ud += analogRead(this->ud);
  }

  return {.lr = (unsigned char)(lr / 255), .ud = (unsigned char)(ud / 255)};
}

void Z_Joystick::begin() {
  pinMode(this->lr, INPUT);
  pinMode(this->ud, INPUT);
}