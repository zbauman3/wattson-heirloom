#include "../config/PinDefs.h"
#include <AceRoutine.h>
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#ifndef Leds_H
#define Leds_H

class LedRoutine : public ace_routine::Coroutine {
private:
  Adafruit_MCP23X17 *mcp;
  unsigned char pin;

  // 0: off
  // 1: flash
  unsigned char routine;

  void set(unsigned char state);

public:
  LedRoutine(Adafruit_MCP23X17 *mcpPtr, unsigned char pin);

  int runCoroutine() override;
  void flash();
  void begin();
};

class Leds {
private:
  LedRoutine *greenRoutine;
  LedRoutine *redRoutine;

public:
  Leds(Adafruit_MCP23X17 *mcpPtr);
  void begin();
  void loop();
  void flashGreen();
  void flashRed();
};

#endif