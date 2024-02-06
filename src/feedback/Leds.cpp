#include "./Leds.h"
using namespace ace_routine;

//--------LedRoutine

LedRoutine::LedRoutine(Adafruit_MCP23X17 *mcpPtr, unsigned char pin) {
  this->mcp = mcpPtr;
  this->pin = pin;
  this->routine = 0;
}

void LedRoutine::begin() {
  this->mcp->pinMode(this->pin, OUTPUT);
  this->set(LOW);
}

void LedRoutine::set(unsigned char state) {
  this->mcp->digitalWrite(this->pin, state);
}

int LedRoutine::runCoroutine() {
  COROUTINE_BEGIN();

  if (this->routine == 1) {
    this->set(HIGH);
    COROUTINE_DELAY(150);
    this->set(LOW);
  }

  this->routine = 0;

  COROUTINE_END();
}

void LedRoutine::flash() {
  this->routine = 1;
  this->reset();
}

//--------Leds

Leds::Leds(Adafruit_MCP23X17 *mcpPtr) {
  this->greenRoutine = new LedRoutine(mcpPtr, PinDefs::mcp_ledGreen);
  this->redRoutine = new LedRoutine(mcpPtr, PinDefs::mcp_ledRed);
}

void Leds::begin() {
  this->greenRoutine->begin();
  this->redRoutine->begin();
}

void Leds::loop() {
  this->greenRoutine->runCoroutine();
  this->redRoutine->runCoroutine();
}

void Leds::flashGreen() { this->greenRoutine->flash(); }

void Leds::flashRed() { this->redRoutine->flash(); }