#include "./Joystick.h"
#include "./Macros.h"
#include "./PinDefs.h"
#include "./State.h"
#include "./src/views/DebugView.h"
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

  DebugView debugView;

public:
  Screen(State *statePtr, Adafruit_MCP23X17 *mcpPtr, Joystick *joystickPtr);
  void begin();
  void loop();
  void setBrightness(unsigned char brightness);
  void toggleBrightness();
};

#endif