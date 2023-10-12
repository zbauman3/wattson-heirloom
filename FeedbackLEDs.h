#include "./PinDefs.h"
#include <AceRoutine.h>
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#ifndef FeedbackLEDs_H
#define FeedbackLEDs_H

class FeedbackLEDRoutine : public ace_routine::Coroutine {
private:
  Adafruit_MCP23X17 *mcp;
  unsigned char pin;

  // 0: off
  // 1: flash
  unsigned char routine;

  void set(unsigned char state);

public:
  FeedbackLEDRoutine(Adafruit_MCP23X17 *mcpPtr, unsigned char pin);

  int runCoroutine() override;
  void flash();
  void begin();
};

class FeedbackLEDs {
private:
  FeedbackLEDRoutine *greenRoutine;
  FeedbackLEDRoutine *redRoutine;

public:
  FeedbackLEDs(Adafruit_MCP23X17 *mcpPtr);
  void begin();

  void flashGreen();
  void flashRed();
};

#endif