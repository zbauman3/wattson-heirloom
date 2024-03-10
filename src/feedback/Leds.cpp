#include "./Leds.h"
using namespace ace_routine;

//--------LedRoutine

LedRoutine::LedRoutine(Adafruit_MCP23X17 *mcpPtr, uint8_t pin) {
  this->mcp = mcpPtr;
  this->pin = pin;
  this->routine = 0;
  this->routineDelay = 0;
}

void LedRoutine::begin() {
  this->mcp->pinMode(this->pin, OUTPUT);
  this->set(LOW);
}

void LedRoutine::set(uint8_t state) {
  this->mcp->digitalWrite(this->pin, state);
}

int LedRoutine::runCoroutine() {
  COROUTINE_LOOP() {
    if (this->routine == 1) {
      this->set(HIGH);
      COROUTINE_DELAY(this->routineDelay);
      this->set(LOW);
      COROUTINE_DELAY(this->routineDelay);
    } else if (this->routine == 2) {
      this->set(HIGH);
      COROUTINE_DELAY(this->routineDelay);
      this->set(LOW);
      this->routine = 0;
    }

    COROUTINE_YIELD();
  }
}

void LedRoutine::flash(uint16_t delay, bool restart) {
  bool isChange = this->routine != 1;

  this->routine = 1;
  this->routineDelay = delay;

  if (isChange || restart) {
    this->set(LOW);
    this->reset();
  }
}

void LedRoutine::flashOnce(uint16_t length, bool restart) {
  bool isChange = this->routine != 2;

  this->routine = 2;
  this->routineDelay = length;

  if (isChange || restart) {
    this->set(LOW);
    this->reset();
  }
}

void LedRoutine::clear() {
  this->routine = 0;
  this->routineDelay = 0;
  this->set(LOW);
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

void Leds::flash(uint8_t which, uint16_t delay, bool restart) {
  if (which == LEDS_GREEN) {
    this->greenRoutine->flash(delay, restart);
  } else {
    this->redRoutine->flash(delay, restart);
  }
}

void Leds::flashOnce(uint8_t which, uint16_t length, bool restart) {
  if (which == LEDS_GREEN) {
    this->greenRoutine->flashOnce(length, restart);
  } else {
    this->redRoutine->flashOnce(length, restart);
  }
}

void Leds::clear(uint8_t which) {
  if (which == LEDS_GREEN) {
    this->greenRoutine->clear();
  } else {
    this->redRoutine->clear();
  }
}