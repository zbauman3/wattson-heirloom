#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#ifndef MiscIO_H
#define MiscIO_H

#define MIO_MENU 0x0
#define MIO_UP 0x1
#define MIO_RECORD 0x2
#define MIO_LEFT 0x3
#define MIO_DOWN 0x4
#define MIO_RIGHT 0x5
#define MIO_ONE 0x6
#define MIO_TWO 0x7
#define MIO_TRIGGER 0x8
#define MIO_POWER 0x9

#define MIO_PIN_COUNT 10

typedef struct {
  char pins[MIO_PIN_COUNT];
  char length;
} micsIOPins;

class MiscIO {
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
  unsigned char trigger;
  unsigned char power;

  unsigned char keyCodeToPin(unsigned char keyCode);

public:
  MiscIO(Adafruit_MCP23X17 *mcpPtr, unsigned char menuPin, unsigned char upPin,
         unsigned char recordPin, unsigned char leftPin, unsigned char downPin,
         unsigned char rightPin, unsigned char onePin, unsigned char twoPin,
         unsigned char triggerPin, unsigned char powerPin);

  void begin();
  bool isPressed(unsigned char keyCode);
  micsIOPins getAllPins();
};

#endif