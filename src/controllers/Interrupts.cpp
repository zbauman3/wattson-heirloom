#include "./Interrupts.h"

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
  for (uint8_t i = 0; i < PinDefs::mcpInputPinsLength; i++) {
    uint8_t pin = PinDefs::mcpInputPins[i];
    // set all to input
    this->mcp->pinMode(pin, INPUT_PULLUP);
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

  for (uint8_t i = 0; i < PinDefs::mcpInputPinsLength; i++) {
    // enable/set all pin interrupt modes
    this->mcp->setupInterruptPin(PinDefs::mcpInputPins[i], CHANGE);
  }
}

void Interrupts::loop() {
  if (!this->_mcp_interrupted && !this->_rotary_interrupted) {
    // if this is not an interrupt cycle, reset the state
    this->state->interrupt = STATE_INTR_EMPTY;
    return;
  }

  if (this->_mcp_interrupted) {
    this->_mcp_interrupted = false;
    this->state->interrupt = STATE_INTR_MCP;
    DEBUG_LN("Interrupt - MCP");

    uint16_t capturedInterrupt = this->mcp->getCapturedInterrupt();

    for (uint8_t i = 0; i < PinDefs::mcpInputPinsLength; i++) {
      uint8_t pin = PinDefs::mcpInputPins[i];
      // set value by bitmap
      this->state->setMcpValueByPin(pin,
                                    !((capturedInterrupt & (1 << pin)) >> pin));
    }

    this->mcp->clearInterrupts();

    // The power plug seems to be especially finicky... Read it again to confirm
    this->state->setMcpValueByPin(PinDefs::mcp_power,
                                  !this->mcp->digitalRead(PinDefs::mcp_power));
  }

  if (this->_rotary_interrupted) {
    this->_rotary_interrupted = false;
    // capture this value now, since it will change when read
    signed long lastRotaryValue = this->state->rotary_position;
    bool lastRotaryButton = this->state->rotary_btn;
    signed long rotaryValue = this->rotary->getValue();
    bool rotaryPressed = this->rotary->isPressed();

    if (rotaryValue != lastRotaryValue) {
      DEBUG_F("Interrupt - Rotary: %d\n", rotaryValue);
      this->state->interrupt = STATE_INTR_ROTARY;
    } else if (rotaryPressed != lastRotaryButton) {
      DEBUG_F("Interrupt - Rotary Btn: %d\n", rotaryPressed);
      this->state->interrupt = STATE_INTR_ROTARY_BTN;
    } else {
      DEBUG_LN("Interrupt - Rotary MISS");
      this->state->interrupt = STATE_INTR_EMPTY;
    }
  }
}