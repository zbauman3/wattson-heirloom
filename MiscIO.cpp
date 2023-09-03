#include "./MiscIO.h"
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

MiscIO::MiscIO(Adafruit_MCP23X17 *mcpPtr, unsigned char menuPin,
               unsigned char upPin, unsigned char recordPin,
               unsigned char leftPin, unsigned char downPin,
               unsigned char rightPin, unsigned char onePin,
               unsigned char twoPin, unsigned char triggerPin,
               unsigned char powerPin) {
  this->mcp = mcpPtr;
  this->menu = menuPin;
  this->up = upPin;
  this->record = recordPin;
  this->left = leftPin;
  this->down = downPin;
  this->right = rightPin;
  this->one = onePin;
  this->two = twoPin;
  this->trigger = triggerPin;
  this->power = powerPin;
}

void MiscIO::begin() {
  this->mcp->pinMode(this->menu, INPUT_PULLUP);
  this->mcp->pinMode(this->up, INPUT_PULLUP);
  this->mcp->pinMode(this->record, INPUT_PULLUP);
  this->mcp->pinMode(this->left, INPUT_PULLUP);
  this->mcp->pinMode(this->down, INPUT_PULLUP);
  this->mcp->pinMode(this->right, INPUT_PULLUP);
  this->mcp->pinMode(this->one, INPUT_PULLUP);
  this->mcp->pinMode(this->two, INPUT_PULLUP);
  this->mcp->pinMode(this->trigger, INPUT_PULLUP);
  this->mcp->pinMode(this->power, INPUT_PULLUP);
}

unsigned char MiscIO::keyCodeToPin(unsigned char keyCode) {
  switch (keyCode) {
  case MIO_MENU:
    return this->menu;
  case MIO_UP:
    return this->up;
  case MIO_RECORD:
    return this->record;
  case MIO_LEFT:
    return this->left;
  case MIO_DOWN:
    return this->down;
  case MIO_RIGHT:
    return this->right;
  case MIO_ONE:
    return this->one;
  case MIO_TWO:
    return this->two;
  case MIO_TRIGGER:
    return this->trigger;
  case MIO_POWER:
  default:
    return this->power;
  }
}

bool MiscIO::isPressed(unsigned char keyCode) {
  if (!this->mcp->digitalRead(this->keyCodeToPin(keyCode))) {
    return true;
  } else {
    return false;
  }
}

micsIOPins MiscIO::getAllPins() {
  char allPins[] = {this->menu,    this->up,    this->record, this->left,
                    this->down,    this->right, this->one,    this->two,
                    this->trigger, this->power};

  return (micsIOPins){.pins = allPins, .length = 10};
}