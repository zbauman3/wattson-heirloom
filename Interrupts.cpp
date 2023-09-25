#include "./Interrupts.h"
#include "./Macros.h"
#include "./PinDefs.h"
#include "./Rotary.h"
#include "./State.h"
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

// can't pass in a class method, need to wrap with this hack.
Interrupts *mainInterruptHandler;
void isr() { mainInterruptHandler->_interrupted = true; }

Interrupts::Interrupts(State *statePtr, Adafruit_MCP23X17 *mcpPtr,
                       Rotary *rotaryPtr) {
  mainInterruptHandler = this;
  this->state = statePtr;
  this->mcp = mcpPtr;
  this->rotary = rotaryPtr;
  this->_interrupted = false;
};

void Interrupts::begin() {
  this->clearTime = millis();

  for (unsigned char i = 0; i < PinDefs::mcpInputPinsLength; i++) {
    unsigned char pin = PinDefs::mcpInputPins[i];
    // set all to input
    this->mcp->pinMode(pin, INPUT_PULLUP);
    // set init states for all inputs
    this->state->setMcpValueByPin(pin, false);
  }

  // enable waterfall interrupts
  this->mcp->pinMode(PinDefs::mcp_rotaryInt, INPUT_PULLUP);

  pinMode(PinDefs::interrupts, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PinDefs::interrupts), isr, FALLING);

  this->mcp->setupInterrupts(true, false, LOW);
  // enable interrupts
  this->rotary->enableInterrupts();

  for (unsigned char i = 0; i < PinDefs::mcpInputPinsLength; i++) {
    // enable/set all pin interrupt modes
    this->mcp->setupInterruptPin(PinDefs::mcpInputPins[i], CHANGE);
  }

  // waterfall interrupts only matter on their initial transition
  this->mcp->setupInterruptPin(PinDefs::mcp_rotaryInt, LOW);
}

void Interrupts::loop() {
  unsigned long nowTime = millis();

  // TODO this `clearTime` check is a hack for when interrupts hang. Seems to be
  // that the `_interrupted` flag get changed between check and reset
  if (!this->_interrupted &&
      nowTime - this->clearTime < INTERRUPTS_MAX_CLEAR_MS) {
    // if this is not an interrupt cycle, reset the state
    if (this->state->hasInterrupt()) {
      this->state->interrupt.type = STATE_INTR_EMPTY;
    }

    return;
  }

  this->_interrupted = false;
  this->clearTime = nowTime;

  unsigned char mcpPin = this->mcp->getLastInterruptPin();

  DEBUG_BLOCK({
    if (mcpPin != 255) {
      DEBUG_F("Interrupt - MCP: %d\n", mcpPin);
    }
  });

  // TODO this `mcpPin != 255` check can be removed after the `clearTime` hack
  if (mcpPin != PinDefs::mcp_rotaryInt && mcpPin != 255) {
    this->state->interrupt.type = STATE_INTR_MCP;
    this->state->interrupt.mcp = mcpPin;

    unsigned int capturedInterrupt = this->mcp->getCapturedInterrupt();
    DEBUG("Captured interrupt: ");
    DEBUG_LN(capturedInterrupt, BIN);

    for (unsigned char i = 0; i < PinDefs::mcpInputPinsLength; i++) {
      unsigned char pin = PinDefs::mcpInputPins[i];
      // set value by bitmap
      this->state->setMcpValueByPin(pin,
                                    !((capturedInterrupt & (1 << pin)) >> pin));
    }

    this->mcp->clearInterrupts();
    return;
  }

  // capture this value now, since it will change when read
  signed long lastRotaryValue = this->state->rotary_position;
  bool lastRotaryButton = this->state->rotary_btn;
  signed long rotaryValue = this->rotary->getValue();
  bool rotaryPressed = this->rotary->isPressed();

  if (rotaryValue != lastRotaryValue) {
    DEBUG_F("Rotary: %d\n", rotaryValue);
    this->state->interrupt.type = STATE_INTR_ROTARY;
    this->state->interrupt.rotary = rotaryValue;
  } else if (rotaryPressed != lastRotaryButton) {
    DEBUG_F("Rotary Btn %d\n", rotaryPressed);
    this->state->interrupt.type = STATE_INTR_ROTARY_BTN;
    this->state->interrupt.rotaryPressed = rotaryPressed;
  } else {
    // DEBUG_LN("MISS");
    // DEBUG_F("Rotary: %d\n", rotaryValue);
    // DEBUG_F("Rotary Btn %d\n", rotaryPressed);
    this->state->interrupt.type = STATE_INTR_EMPTY;
  }

  this->mcp->clearInterrupts();
}