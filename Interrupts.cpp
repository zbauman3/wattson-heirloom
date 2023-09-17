#include "./Interrupts.h"
#include "./Macros.h"
#include "./Rotary.h"
#include "./State.h"
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

// can't pass in a class method, need to wrap with this hack.
Interrupts *mainInterruptHandler;
void isr() { mainInterruptHandler->_handleInterrupt(); }

Interrupts::Interrupts(State *statePtr, Adafruit_MCP23X17 *mcpPtr,
                       Rotary *rotaryPtr, MiscIO *miscIOPtr,
                       char interruptPin) {
  mainInterruptHandler = this;
  this->state = statePtr;
  this->mcp = mcpPtr;
  this->rotary = rotaryPtr;
  this->miscIO = miscIOPtr;
  this->interrupted = false;
  this->interruptPin = interruptPin;
};

void Interrupts::begin() {
  pinMode(this->interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(this->interruptPin), isr, FALLING);

  this->lastRotaryValue = this->rotary->getValue();
  this->mcp->setupInterrupts(true, false, LOW);
  this->rotary->enableInterrupts();

  micsIOPins allMiscIOPins = this->miscIO->getAllPins();

  for (char i = 0; i < allMiscIOPins.length; i++) {
    if (this->miscIO->rotaryInt == allMiscIOPins.pins[i]) {
      this->mcp->setupInterruptPin(allMiscIOPins.pins[i], LOW);
    } else {
      this->mcp->setupInterruptPin(allMiscIOPins.pins[i], CHANGE);
    }
  }
}

void Interrupts::loop() {
  if (!this->interrupted) {
    // if this is not an interrupt cycle, reset the state
    if (this->state->hasInterrupt()) {
      this->state->interrupt.type = STATE_INTR_EMPTY;
    }

    return;
  }
  this->interrupted = false;

  DEBUG_LN("---Interrupt---");

  unsigned char mcpPin = this->mcp->getLastInterruptPin();
  if (mcpPin < 255) {
    DEBUG_F("MCP: %d\n", mcpPin);
    DEBUG("Captured interrupt: ");
    DEBUG_LN(this->mcp->getCapturedInterrupt(), BIN);
    this->state->interrupt.type = STATE_INTR_MCP;
    this->state->interrupt.mcp = mcpPin;
    this->mcp->clearInterrupts();

    if (mcpPin != this->miscIO->rotaryInt) {
      return;
    }
  }

  signed long rotaryValue = this->rotary->getValue();
  if (rotaryValue != this->lastRotaryValue) {
    DEBUG_F("Rotary: %d\n", rotaryValue);
    this->state->interrupt.type = STATE_INTR_ROTARY;
    this->state->interrupt.rotary = rotaryValue;
    this->lastRotaryValue = rotaryValue;
    return;
  }

  bool rotaryPressed = this->rotary->isPressed();
  if (rotaryPressed) {
    DEBUG_F("Rotary Btn %d\n", rotaryPressed);
    this->state->interrupt.type = STATE_INTR_ROTARY_BTN;
    this->state->interrupt.rotaryPressed = rotaryPressed;
    return;
  }

  DEBUG_BLOCK({
    DEBUG_F("MCP: %d\n", mcpPin);
    DEBUG_F("Rotary: %d\n", rotaryValue);
    DEBUG_F("Rotary Btn %d\n", rotaryPressed);
    DEBUG("Captured interrupt: ");
    DEBUG_LN(this->mcp->getCapturedInterrupt(), BIN);
  });

  // TODO this should likely just be the rotary. Do that?
  //
  // could be rotary button up, could be mcp and something read / wrote to it
  // before we could read `getLastInterruptPin`
  this->state->interrupt.type = STATE_INTR_EMPTY;
  this->state->interrupt.mcp = 0;
  this->mcp->clearInterrupts();
}

void Interrupts::_handleInterrupt() { this->interrupted = true; }