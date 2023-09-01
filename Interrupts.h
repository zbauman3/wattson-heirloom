
#include "./Macros.h"
#include "./Rotary.h"
#include "./State.h"
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#ifndef Interrupts_H
#define Interrupts_H

class Interrupts {
private:
  bool interrupted;
  unsigned int lastInterruptTime;
  signed long lastRotaryValue;
  State *state;
  Adafruit_MCP23X17 *mcp;
  Rotary *rotary;

public:
  Interrupts(State *statePtr, Adafruit_MCP23X17 *mcpPtr, Rotary *rotaryPtr);

  void begin(char mcpPins[10]);
  void loop();
  void handleInterrupt();
};

#endif