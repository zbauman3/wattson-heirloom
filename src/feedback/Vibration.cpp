#include "./Vibration.h"
using namespace ace_routine;

Vibration::Vibration() { this->routine = 0; }

void Vibration::begin() {
  pinMode(PinDefs::vibe, OUTPUT);
  analogWriteResolution(8);
  this->set(0);
}

void Vibration::set(unsigned char value) { analogWrite(PinDefs::vibe, value); }

int Vibration::runCoroutine() {
  COROUTINE_BEGIN();
  if (this->routine == 1) {
    this->set(0);

    for (this->routineLoop = 1; this->routineLoop <= 10; this->routineLoop++) {
      if (this->routineLoop % 2 == 0) {
        this->set(255);
      } else {
        this->set(0);
      }

      float percent = this->routineLoop / float(10);
      COROUTINE_DELAY(char(650 - (500 / percent)));
    }

    this->set(255);
    COROUTINE_DELAY(500);
    this->set(0);
  }

  this->routine = 0;

  COROUTINE_END();
}

void Vibration::startPattern(unsigned char which) {
  if (which <= 0 || which > 1) {
    return;
  }

  this->routine = which;
  this->reset();
}