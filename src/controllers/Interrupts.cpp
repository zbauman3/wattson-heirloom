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
  this->trueUpTime = 0;

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

// Sometimes seeing interrupts not getting handled correctly.
// This checks every few seconds to avoid missed state changes
void Interrupts::trueUp() {
  unsigned long nowTime = millis();

  if (nowTime - this->trueUpTime < 7500) {
    return;
  }

  this->trueUpTime = nowTime;
  this->readMcp();
  this->readRotary();
}

void Interrupts::readMcp() {
  uint16_t capturedInterrupt = this->mcp->getCapturedInterrupt();

  for (uint8_t i = 0; i < PinDefs::mcpInputPinsLength; i++) {
    uint8_t pin = PinDefs::mcpInputPins[i];
    // set value by bitmap
    this->state->setMcpValueByPin(pin,
                                  !((capturedInterrupt & (1 << pin)) >> pin));
  }

  this->mcp->clearInterrupts();
}

// return:
// STATE_INTR_ROTARY
// STATE_INTR_ROTARY_BTN
uint8_t Interrupts::readRotary() {
  // capture this value now, since it will change when read
  bool lastRotaryButton = this->state->rotary_btn;
  bool rotaryPressed = this->rotary->isPressed();
  this->rotary->getValue();

  if (rotaryPressed != lastRotaryButton) {
    return STATE_INTR_ROTARY_BTN;
  }

  return STATE_INTR_ROTARY;
}

void Interrupts::loop() {
  if (!this->_mcp_interrupted && !this->_rotary_interrupted) {
    // if this is not an interrupt cycle, reset the state
    this->state->interrupt = STATE_INTR_EMPTY;
    this->trueUp();
    return;
  }

  if (this->_mcp_interrupted) {
    this->_mcp_interrupted = false;
    this->readMcp();
    this->state->interrupt = STATE_INTR_MCP;
    DEBUG_LN("Interrupt - MCP");
  }

  if (this->_rotary_interrupted) {
    this->_rotary_interrupted = false;
    this->state->interrupt = this->readRotary();

    if (this->state->interrupt == STATE_INTR_ROTARY_BTN) {
      DEBUG_LN("Interrupt - Rotary Btn");
    } else {
      DEBUG_LN("Interrupt - Rotary");
    }
  }
}