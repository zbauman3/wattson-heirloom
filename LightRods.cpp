#include "./LightRods.h"
#include "./PinDefs.h"
#include <AceRoutine.h>
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
using namespace ace_routine;

#define NEOPIXEL_COUNT 1
// #define NEOPIXEL_COUNT 144

LightRods::LightRods()
    : neopixels(Adafruit_NeoPixel(NEOPIXEL_COUNT, PinDefs::neopixels,
                                  NEO_RGB + NEO_KHZ800)) {}

void LightRods::begin() {
  this->neopixels.begin();
  this->neopixels.setBrightness(30);
  this->off();
}

int LightRods::runCoroutine() {
  COROUTINE_BEGIN();

  if (this->routine == 1) {
    for (this->routineLoop = 1; this->routineLoop <= 10; this->routineLoop++) {
      float percent = this->routineLoop / float(10);

      if (this->routineLoop % 2 == 0) {
        this->neopixels.fill(neopixels.Color(
            char(255 * percent), char(25 * percent), char(25 * percent)));
        this->neopixels.show();
      } else {
        this->off();
      }

      COROUTINE_DELAY(char(650 - (500 / percent)));
    }

    this->neopixels.fill(neopixels.Color(255, 25, 25));
    this->neopixels.show();
    COROUTINE_DELAY(500);
    this->off();
  }

  this->routine = 0;

  COROUTINE_END();
}

void LightRods::off() {
  this->neopixels.fill(neopixels.Color(0, 0, 0));
  this->neopixels.show();
}

void LightRods::startPattern(unsigned char which) {
  if (which <= 0 || which > 1) {
    return;
  }

  this->routine = which;
  this->reset();
}
