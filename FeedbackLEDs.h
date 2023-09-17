#include "./PinDefs.h"
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#ifndef FeedbackLEDs_H
#define FeedbackLEDs_H

class FeedbackLEDs {
private:
  Adafruit_MCP23X17 *mcp;

  void set(unsigned char which, unsigned char state);

public:
  FeedbackLEDs(Adafruit_MCP23X17 *mcpPtr);
  void begin();

  void setGreen(unsigned char state);
  void setRed(unsigned char state);
};

#endif