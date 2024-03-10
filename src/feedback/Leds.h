#include "../config/PinDefs.h"
#include <AceRoutine.h>
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#ifndef Leds_H
#define Leds_H

#define LEDS_GREEN 0x00
#define LEDS_RED 0x01

class LedRoutine : public ace_routine::Coroutine {
private:
  Adafruit_MCP23X17 *mcp;
  uint8_t pin;

  // 0: off
  // 1: flash
  // 1: flashOnce
  uint8_t routine;
  uint16_t routineDelay;

public:
  LedRoutine(Adafruit_MCP23X17 *mcpPtr, uint8_t pin);

  int runCoroutine() override;
  void begin();
  void set(uint8_t state);
  void flash(uint16_t delay, bool restart = false);
  void flashOnce(uint16_t length, bool restart = false);
  void clear();
};

class Leds {
private:
  LedRoutine *greenRoutine;
  LedRoutine *redRoutine;

public:
  Leds(Adafruit_MCP23X17 *mcpPtr);
  void begin();
  void loop();
  void flash(uint8_t which, uint16_t delay, bool restart = false);
  void flashOnce(uint8_t which, uint16_t length, bool restart = false);
  void clear(uint8_t which);
};

#endif