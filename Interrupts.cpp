#include "./Interrupts.h"
#include "./Macros.h"
#include "./PinDefs.h"
#include "./Rotary.h"
#include "./State.h"
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

// can't pass in a class method, need to wrap with this hack.
Interrupts *mainInterruptHandler;
void mcp_isr() { mainInterruptHandler->_mcp_interrupted = true; }
void rotary_isr() { mainInterruptHandler->_rotary_interrupted = true; }

Interrupts::Interrupts(State *statePtr, Adafruit_MCP23X17 *mcpPtr,
                       Rotary *rotaryPtr) {
  mainInterruptHandler = this;
  this->state = statePtr;
  this->mcp = mcpPtr;
  this->rotary = rotaryPtr;
  this->_mcp_interrupted = false;
  this->_rotary_interrupted = false;
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

  pinMode(PinDefs::mcp_interrupts, INPUT_PULLUP);
  pinMode(PinDefs::rotary_interrupts, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PinDefs::mcp_interrupts), mcp_isr,
                  FALLING);
  attachInterrupt(digitalPinToInterrupt(PinDefs::rotary_interrupts), rotary_isr,
                  FALLING);

  this->mcp->setupInterrupts(true, false, LOW);
  // enable interrupts
  this->rotary->enableInterrupts();

  for (unsigned char i = 0; i < PinDefs::mcpInputPinsLength; i++) {
    // enable/set all pin interrupt modes
    this->mcp->setupInterruptPin(PinDefs::mcpInputPins[i], CHANGE);
  }
}

void Interrupts::loop() {
  unsigned long nowTime = millis();

  if (!this->_mcp_interrupted && !this->_rotary_interrupted) {
    // if this is not an interrupt cycle, reset the state
    this->state->interrupt.type = STATE_INTR_EMPTY;
    return;
  }

  if (this->_mcp_interrupted) {
    this->_mcp_interrupted = false;
    unsigned char mcpPin = this->mcp->getLastInterruptPin();
    unsigned int capturedInterrupt = this->mcp->getCapturedInterrupt();

    this->state->interrupt.type = STATE_INTR_MCP;
    this->state->interrupt.mcp = mcpPin;

    DEBUG_F("Interrupt - MCP: %d\n", mcpPin);
    DEBUG("Captured interrupt: ");
    DEBUG_LN(capturedInterrupt, BIN);

    for (unsigned char i = 0; i < PinDefs::mcpInputPinsLength; i++) {
      unsigned char pin = PinDefs::mcpInputPins[i];
      // set value by bitmap
      this->state->setMcpValueByPin(pin,
                                    !((capturedInterrupt & (1 << pin)) >> pin));
    }

    this->mcp->clearInterrupts();
  }

  if (this->_rotary_interrupted) {
    this->_rotary_interrupted = false;
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
  }
}