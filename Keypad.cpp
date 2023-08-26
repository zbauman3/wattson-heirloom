#include "./Keypad.h"
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

Keypad::Keypad(Adafruit_MCP23X17 *mcpPtr, unsigned char menuPin,
               unsigned char upPin, unsigned char recordPin,
               unsigned char leftPin, unsigned char downPin,
               unsigned char rightPin, unsigned char onePin,
               unsigned char twoPin) {
  this->mcp = mcpPtr;
  this->menu = menuPin;
  this->up = upPin;
  this->record = recordPin;
  this->left = leftPin;
  this->down = downPin;
  this->right = rightPin;
  this->one = onePin;
  this->two = twoPin;
}

void Keypad::begin() {
  this->mcp->pinMode(this->menu, INPUT_PULLUP);
  this->mcp->pinMode(this->up, INPUT_PULLUP);
  this->mcp->pinMode(this->record, INPUT_PULLUP);
  this->mcp->pinMode(this->left, INPUT_PULLUP);
  this->mcp->pinMode(this->down, INPUT_PULLUP);
  this->mcp->pinMode(this->right, INPUT_PULLUP);
  this->mcp->pinMode(this->one, INPUT_PULLUP);
  this->mcp->pinMode(this->two, INPUT_PULLUP);
}

unsigned char Keypad::keyCodeToPin(unsigned char keyCode) {
  switch (keyCode) {
  case KEYPAD_MENU:
    return this->menu;
  case KEYPAD_UP:
    return this->up;
  case KEYPAD_RECORD:
    return this->record;
  case KEYPAD_LEFT:
    return this->left;
  case KEYPAD_DOWN:
    return this->down;
  case KEYPAD_RIGHT:
    return this->right;
  case KEYPAD_ONE:
    return this->one;
  case KEYPAD_TWO:
  default:
    return this->two;
  }
}

bool Keypad::isPressed(unsigned char keyCode) {
  if (!this->mcp->digitalRead(this->keyCodeToPin(keyCode))) {
    return true;
  } else {
    return false;
  }
}