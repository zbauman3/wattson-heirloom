
#include "./Macros.h"
#include "./MiscIO.h"
#include "./Rotary.h"
#include "./State.h"
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#ifndef Interrupts_H
#define Interrupts_H

class Interrupts {
private:
  char interruptPin;
  bool interrupted;
  signed long lastRotaryValue;
  State *state;
  Adafruit_MCP23X17 *mcp;
  Rotary *rotary;
  MiscIO *miscIO;

public:
  Interrupts(State *statePtr, Adafruit_MCP23X17 *mcpPtr, Rotary *rotaryPtr,
             MiscIO *miscIOPtr, char interruptPin);

  void begin();
  void loop();

  void _handleInterrupt();
};

#endif