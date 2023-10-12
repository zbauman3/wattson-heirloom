#define DEBUG_ENABLED 0

#include <Arduino.h>

#ifndef Macros_H
#define Macros_H

#if (defined(DEBUG_ENABLED) && DEBUG_ENABLED == 1)
#define DEBUG_INIT(rate) Serial.begin(rate)
#define DEBUG_LN(...) Serial.println(__VA_ARGS__)
#define DEBUG_F(...) Serial.printf(__VA_ARGS__)
#define DEBUG(...) Serial.print(__VA_ARGS__)
#define DEBUG_BLOCK(...) __VA_ARGS__
#else
#define DEBUG_INIT
#define DEBUG_LN
#define DEBUG_F
#define DEBUG
#define DEBUG_BLOCK
#endif

#define INFINITE_LOOP                                                          \
  while (1)                                                                    \
  delay(10)

#endif