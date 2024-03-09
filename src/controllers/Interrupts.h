
#include "../config/Macros.h"
#include "../config/PinDefs.h"
#include "../models/State.h"
#include "./Rotary.h"
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#ifndef Interrupts_H
#define Interrupts_H

#define INTERRUPTS_MAX_CLEAR_MS 2000

class Interrupts {
private:
  unsigned long trueUpTime;
  State *state;
  Adafruit_MCP23X17 *mcp;
  Rotary *rotary;

public:
  volatile bool _mcp_interrupted;
  volatile bool _rotary_interrupted;
  Interrupts(State *statePtr, Adafruit_MCP23X17 *mcpPtr, Rotary *rotaryPtr);

  void begin();
  void loop();
  void trueUp();
  void readMcp();
  uint8_t readRotary();
};

#endif