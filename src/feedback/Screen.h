#include "../config/Macros.h"
#include "../config/PinDefs.h"
#include "../controllers/Joystick.h"
#include "../models/State.h"
#include "../views/DebugView.h"
#include "../views/RadarView.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#ifndef Screen_H
#define Screen_H

class Screen {
private:
  Adafruit_ILI9341 tft;
  Adafruit_MCP23X17 *mcp;
  State *state;
  Joystick *joystick;
  uint8_t activeView;
  bool switchedView;

  DebugView debugView;
  RadarView radarView;

public:
  Screen(State *statePtr, Adafruit_MCP23X17 *mcpPtr, Joystick *joystickPtr);
  void begin();
  void loop();
  void setBrightness(unsigned char brightness);
  void toggleBrightness();
  void setActiveView(uint8_t view);
};

#endif