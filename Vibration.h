#include "./Macros.h"
#include "./PinDefs.h"
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#ifndef Vibration_H
#define Vibration_H

class Vibration {
private:
  Adafruit_MCP23X17 *mcp;

public:
  Vibration(Adafruit_MCP23X17 *mcpPtr);

  void begin();
  void tmp_vibrate();
};

#endif