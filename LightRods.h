#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#ifndef LightRods_h
#define LightRods_h

class LightRods {
private:
  Adafruit_NeoPixel neopixels;
  unsigned int count;

public:
  LightRods(unsigned int count, signed int pin);
  void begin();
  void off();

  void tmp_fill(unsigned char r, unsigned char g, unsigned char b);
};

#endif