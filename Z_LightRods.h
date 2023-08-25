#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#ifndef Z_LightRods_h
#define Z_LightRods_h

class Z_LightRods {
private:
  Adafruit_NeoPixel neopixels;
  unsigned int count;

public:
  Z_LightRods(unsigned int count, signed int pin);
  void begin();
  void off();

  void tmp_fill(unsigned char r, unsigned char g, unsigned char b);
};

#endif