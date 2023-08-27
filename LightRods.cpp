#include "./LightRods.h"
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

LightRods::LightRods(unsigned int count, signed int pin)
    : neopixels(Adafruit_NeoPixel(count, pin, NEO_RGB + NEO_KHZ800)) {
  this->count = count;
}

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
