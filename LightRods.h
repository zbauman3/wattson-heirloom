#include "./PinDefs.h"
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#ifndef LightRods_h
#define LightRods_h

class LightRods {
private:
  Adafruit_NeoPixel neopixels;

public:
  LightRods();
  void begin();
  void off();

  void tmp_fill(unsigned char r, unsigned char g, unsigned char b);
};

#endif