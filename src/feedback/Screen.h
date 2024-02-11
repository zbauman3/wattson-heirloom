#include "../config/Macros.h"
#include "../config/PinDefs.h"
#include "../models/State.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#ifndef Screen_H
#define Screen_H

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_CENTER_X 160
#define SCREEN_CENTER_Y 120

#define COLOR_GREEN_FOREGND 0x060f
#define COLOR_BLACK 0x0000

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