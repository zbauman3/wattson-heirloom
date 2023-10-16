#include "./Macros.h"
#include "./PinDefs.h"
#include <AceRoutine.h>
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#ifndef Vibration_H
#define Vibration_H

class Vibration : public ace_routine::Coroutine {
private:
  Adafruit_MCP23X17 *mcp;

  // 0: off
  // 1: trigger - quick
  unsigned char routine;
  unsigned short int routineLoop;

public:
  Vibration(Adafruit_MCP23X17 *mcpPtr);

  int runCoroutine() override;
  void begin();

  void startPattern(unsigned char which);
};

#endif