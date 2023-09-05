#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#ifndef Vibration_H
#define Vibration_H

class Vibration {
private:
  Adafruit_MCP23X17 *mcp;
  unsigned char vibeLeft;
  unsigned char vibeRight;

public:
  Vibration(Adafruit_MCP23X17 *mcpPtr, unsigned char vibeLeftPin,
            unsigned char vibeRightPin);

  void begin();
  void tmp_vibrate();
};

#endif