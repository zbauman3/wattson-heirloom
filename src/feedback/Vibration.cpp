#include "./Vibration.h"
using namespace ace_routine;

Vibration::Vibration() { this->routine = 0; }

void Vibration::begin() {
  pinMode(PinDefs::vibe, OUTPUT);
  analogWriteResolution(8);
  this->set(0);
}

void Vibration::set(uint8_t value) { analogWrite(PinDefs::vibe, value); }

int Vibration::runCoroutine() {
  COROUTINE_BEGIN();
  if (this->routine == 1) {
    this->routine = 0;
  }

  COROUTINE_END();
}

void Vibration::startPattern(uint8_t which) {
  if (which <= 0 || which > 1) {
    return;
  }

  this->routine = which;
  this->reset();
}