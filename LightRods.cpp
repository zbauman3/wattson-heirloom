#include "./LightRods.h"
#include "./PinDefs.h"
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#define NEOPIXEL_COUNT 1 // 144

LightRods::LightRods()
    : neopixels(Adafruit_NeoPixel(NEOPIXEL_COUNT, PinDefs::neopixels,
                                  NEO_RGB + NEO_KHZ800)) {}

void LightRods::begin() {
  this->neopixels.begin();
  this->neopixels.setBrightness(10);
  this->off();
}

void LightRods::off() {
  this->neopixels.fill(neopixels.Color(0, 0, 0));
  this->neopixels.show();
}

void LightRods::tmp_fill(unsigned char r, unsigned char g, unsigned char b) {
  this->neopixels.fill(neopixels.Color(r, g, b));
  this->neopixels.show();
}
