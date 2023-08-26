#include "./LightRods.h"
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

Z_LightRods::Z_LightRods(unsigned int count, signed int pin)
    : neopixels(Adafruit_NeoPixel(count, pin, NEO_RGB + NEO_KHZ800)) {
  this->count = count;
}

void Z_LightRods::begin() {
  this->neopixels.begin();
  this->off();
}

void Z_LightRods::off() {
  this->neopixels.fill(neopixels.Color(0, 0, 0));
  this->neopixels.show();
}

void Z_LightRods::tmp_fill(unsigned char r, unsigned char g, unsigned char b) {
  this->neopixels.fill(neopixels.Color(r, g, b));
  this->neopixels.show();
}
