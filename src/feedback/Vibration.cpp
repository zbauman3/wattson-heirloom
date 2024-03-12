#include "./Vibration.h"
using namespace ace_routine;

Vibration::Vibration() { this->routine = 0; }

void Vibration::begin() {
  pinMode(PinDefs::vibe, OUTPUT);
  analogWriteResolution(8);
  this->set(0);
}

void Vibration::set(uint8_t value, bool allowDeadzone) {
  if (value > 0 && value < 75 && !allowDeadzone) {
    value = 75;
  }

  analogWrite(PinDefs::vibe, value);
}

int Vibration::runCoroutine() {
  COROUTINE_LOOP() {
    if (this->routine == VIBE_PATTERN_TRIGGER_INIT) {
      if (this->i == 0) {
        this->i = 1;
        this->set(0);
      } else {
        this->i = 0;
        this->set(200);
      }

      COROUTINE_DELAY(50);
    } else if (this->routine == VIBE_PATTERN_TRIGGER_LOWPOWER) {
      this->set(0);

      for (this->i = 0; this->i < NEOPIXEL_COUNT / 2; this->i++) {
        this->set(((uint8_t)ceil(
            (float)255 * ((float)this->i / (float)(NEOPIXEL_COUNT / 2)))));
        COROUTINE_DELAY(20);
      }

      for (this->i = 125; this->i <= 245; this->i += 10) {
        this->set(this->i);
        COROUTINE_DELAY(15);
      }

      for (this->i = 255; this->i > 100; this->i -= 15) {
        this->set(this->i);
        COROUTINE_DELAY(10);
      }

      this->clear();
    } else if (this->routine == VIBE_PATTERN_TRIGGER_BUILD) {
      this->set(0);

      for (this->i = 0; this->i < NEOPIXEL_COUNT / 2; this->i++) {
        this->set(((uint8_t)ceil(
            (float)255 * ((float)this->i / (float)(NEOPIXEL_COUNT / 2)))));
        COROUTINE_DELAY(100);
      }

      while (true) {
        for (this->i = 125; this->i <= 245; this->i += 10) {
          this->set(this->i);
          COROUTINE_DELAY(25);
        }

        for (this->i = 255; this->i >= 145; this->i -= 10) {
          this->set(this->i);
          COROUTINE_DELAY(25);
        }

        COROUTINE_YIELD();
      }
    } else if (this->routine == VIBE_PATTERN_TRIGGER_HIGHPOWER) {
      this->set(0);

      for (this->j = 0; this->j < 5; this->j++) {
        this->i = 0;
        for (this->k = 0; this->k < 3; this->k++) {
          if (this->i == 0) {
            this->i = 1;
            this->set(150);
          } else {
            this->i = 0;
            this->set(255);
          }
          COROUTINE_DELAY(58);
        }
      }

      for (this->i = 255; this->i >= 10; this->i -= 10) {
        this->set(this->i);
        COROUTINE_DELAY(50);
      }

      this->clear();
    }

    COROUTINE_YIELD();
  }
}

void Vibration::clear() {
  this->routine = 0;
  this->set(0);
  this->reset();
}

bool Vibration::changeRoutine(uint8_t which, bool restart) {
  bool isChange = this->routine != which;
  this->routine = which;
  if (isChange || restart) {
    this->set(0);
    this->reset();
    return true;
  }
  return false;
}

void Vibration::triggerInit() {
  this->i = 0;
  this->changeRoutine(VIBE_PATTERN_TRIGGER_INIT, false);
}

void Vibration::triggerBuild() {
  this->changeRoutine(VIBE_PATTERN_TRIGGER_BUILD, false);
}

void Vibration::triggerHighPower() {
  this->changeRoutine(VIBE_PATTERN_TRIGGER_HIGHPOWER, false);
}

void Vibration::triggerLowPower() {
  this->changeRoutine(VIBE_PATTERN_TRIGGER_LOWPOWER, false);
}