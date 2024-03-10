#include "./LightRods.h"
using namespace ace_routine;

LightRods::LightRods(State *statePtr)
    : neopixels(Adafruit_NeoPixel(NEOPIXEL_COUNT, PinDefs::neopixels,
                                  NEO_GRB + NEO_KHZ800)) {
  this->state = statePtr;
  this->routine = 0;
  this->routineVariation = 0;
}

void LightRods::begin() {
  this->neopixels.begin();
  this->neopixels.setBrightness(30);
  this->off();
}

uint32_t LightRods::getColor(uint8_t r, uint8_t g, uint8_t b) {
  if (this->state->mcp_power) {
    return neopixels.Color(r, g, b);
  }

  return neopixels.Color(max((uint8_t)floor(r / 6), (uint8_t)0),
                         max((uint8_t)floor(g / 6), (uint8_t)0),
                         max((uint8_t)floor(b / 6), (uint8_t)0));
}

int LightRods::runCoroutine() {
  COROUTINE_LOOP() {
    if (this->routine == LIGHTS_PATTERN_RADAR) {
      this->i = 0;
      while (this->i < NEOPIXEL_COUNT + 5) {
        if (this->routineVariation == 1) {
          this->neopixels.setPixelColor(i, this->getColor(255, 100, 0));
        } else {
          this->neopixels.setPixelColor(i, this->getColor(0, 180, 255));
        }
        this->neopixels.setPixelColor(i - 5, this->getColor(0, 0, 0));
        this->neopixels.show();
        COROUTINE_DELAY(50);
        i++;
      }

      this->off();
      this->routine = 0;
    }

    COROUTINE_YIELD();
  }
}

void LightRods::off() {
  this->neopixels.fill(neopixels.Color(0, 0, 0));
  this->neopixels.show();
}

void LightRods::showPattern(uint8_t which, uint8_t variation, bool restart) {
  bool isChange = this->routine != which;

  this->routine = which;
  this->routineVariation = variation;

  if (isChange || restart) {
    this->off();
    this->reset();
  }
}

void LightRods::clear() {
  this->routine = 0;
  this->routineVariation = 0;
  this->off();
  this->reset();
}
