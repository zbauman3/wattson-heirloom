#include "./Joystick.h"
#include "./Macros.h"
#include "./PinDefs.h"
#include "./State.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <AceRoutine.h>
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#ifndef Screen_H
#define Screen_H

class Screen : public ace_routine::Coroutine {
private:
  Adafruit_ILI9341 tft;
  Adafruit_MCP23X17 *mcp;
  State *state;
  Joystick *joystick;

  // 0: off
  // 1: tmp display
  unsigned char routine;
  unsigned short int routineLoop;

public:
  Screen(State *statePtr, Adafruit_MCP23X17 *mcpPtr, Joystick *joystickPtr);
  void begin();
  int runCoroutine() override;
  void setBrightness(unsigned char brightness);
  void toggleBrightness();

  void tmp_display();
};

#endif