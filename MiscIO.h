#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#ifndef MiscIO_H
#define MiscIO_H

#define MIO_PIN_COUNT 11

typedef struct {
  char pins[MIO_PIN_COUNT];
  char length;
} micsIOPins;

class MiscIO {
private:
  Adafruit_MCP23X17 *mcp;

public:
  unsigned char menu;
  unsigned char up;
  unsigned char record;
  unsigned char left;
  unsigned char down;
  unsigned char right;
  unsigned char one;
  unsigned char two;
  unsigned char trigger;
  unsigned char power;
  unsigned char rotaryInt;

  MiscIO(Adafruit_MCP23X17 *mcpPtr, unsigned char menuPin, unsigned char upPin,
         unsigned char recordPin, unsigned char leftPin, unsigned char downPin,
         unsigned char rightPin, unsigned char onePin, unsigned char twoPin,
         unsigned char triggerPin, unsigned char powerPin,
         unsigned char rotaryIntPin);

  void begin();
  bool isPressed(unsigned char mcpPin);
  micsIOPins getAllPins();
};

#endif