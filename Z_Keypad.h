#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#ifndef Z_Keypad_H
#define Z_Keypad_H

#define KEYPAD_MENU 0x0
#define KEYPAD_UP 0x1
#define KEYPAD_RECORD 0x2
#define KEYPAD_LEFT 0x3
#define KEYPAD_DOWN 0x4
#define KEYPAD_RIGHT 0x5
#define KEYPAD_ONE 0x6
#define KEYPAD_TWO 0x7

class Z_Keypad {
private:
  Adafruit_MCP23X17 *mcp;
  unsigned char menu;
  unsigned char up;
  unsigned char record;
  unsigned char left;
  unsigned char down;
  unsigned char right;
  unsigned char one;
  unsigned char two;

  unsigned char keyCodeToPin(unsigned char keyCode);

public:
  Z_Keypad(Adafruit_MCP23X17 *mcpPtr, unsigned char menuPin,
           unsigned char upPin, unsigned char recordPin, unsigned char leftPin,
           unsigned char downPin, unsigned char rightPin, unsigned char onePin,
           unsigned char twoPin);

  void begin();
  bool isPressed(unsigned char keyCode);
};

#endif