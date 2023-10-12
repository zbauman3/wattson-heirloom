#include "./LightRods.h"
#include "./PinDefs.h"
#include <AceRoutine.h>
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
using namespace ace_routine;

#define NEOPIXEL_COUNT 1 // 144

LightRods::LightRods()
    : neopixels(Adafruit_NeoPixel(NEOPIXEL_COUNT, PinDefs::neopixels,
                                  NEO_RGB + NEO_KHZ800)) {}

void LightRods::begin() {
  this->neopixels.begin();
  this->neopixels.setBrightness(10);
  this->off();
}

int LightRods::runCoroutine() {
  COROUTINE_BEGIN();

  if (this->routine == 1) {
    this->neopixels.fill(neopixels.Color(255, 0, 255));
    this->neopixels.show();
    COROUTINE_DELAY(150);
    this->off();
  }

  this->routine = 0;

  COROUTINE_END();
}

void LightRods::off() {
  this->neopixels.fill(neopixels.Color(0, 0, 0));
  this->neopixels.show();
}

void LightRods::tmp_flash() {
  this->routine = 1;
  this->reset();
}
