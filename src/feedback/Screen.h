#include "../config/Macros.h"
#include "../config/PinDefs.h"
#include "../models/State.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#ifndef Screen_H
#define Screen_H

class Screen {
private:
  Adafruit_MCP23X17 *mcp;
  State *state;

public:
  Adafruit_ILI9341 tft;

  Screen(State *statePtr, Adafruit_MCP23X17 *mcpPtr);
  void begin();
  void setBrightness(unsigned char brightness);
  void toggleBrightness();
};

#endif