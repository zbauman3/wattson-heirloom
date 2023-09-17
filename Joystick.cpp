#include "./Joystick.h"
#include "./PinDefs.h"
#include <Arduino.h>

joystickValues Joystick::sample() {
  int lr = 0;
  int ud = 0;

  for (int i = 0; i < NUM_SAMPLES; i++) {
    lr += analogRead(PinDefs::joystickLR);
    ud += analogRead(PinDefs::joystickUD);
  }

  return {.lr = (unsigned char)(lr / NUM_SAMPLES),
          .ud = (unsigned char)(ud / NUM_SAMPLES)};
}

void Joystick::begin() {
  pinMode(PinDefs::joystickLR, INPUT);
  pinMode(PinDefs::joystickUD, INPUT);
}