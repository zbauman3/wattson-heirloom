#include "./FeedbackLEDs.h"
#include "./PinDefs.h"
#include <AceRoutine.h>
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>
using namespace ace_routine;

//--------FeedbackLEDRoutine

FeedbackLEDRoutine::FeedbackLEDRoutine(Adafruit_MCP23X17 *mcpPtr,
                                       unsigned char pin) {
  this->mcp = mcpPtr;
  this->pin = pin;
  this->routine = 0;
}

void FeedbackLEDRoutine::begin() {
  this->mcp->pinMode(this->pin, OUTPUT);
  this->set(LOW);
}

void FeedbackLEDRoutine::set(unsigned char state) {
  this->mcp->digitalWrite(this->pin, state);
}

int FeedbackLEDRoutine::runCoroutine() {
  COROUTINE_BEGIN();

  if (this->routine == 1) {
    this->set(HIGH);
    COROUTINE_DELAY(150);
    this->set(LOW);
  }

  this->routine = 0;

  COROUTINE_END();
}

void FeedbackLEDRoutine::flash() {
  this->routine = 1;
  this->reset();
}

//--------FeedbackLEDs

FeedbackLEDs::FeedbackLEDs(Adafruit_MCP23X17 *mcpPtr) {
  this->greenRoutine = new FeedbackLEDRoutine(mcpPtr, PinDefs::mcp_ledGreen);
  this->redRoutine = new FeedbackLEDRoutine(mcpPtr, PinDefs::mcp_ledRed);
}

void FeedbackLEDs::begin() {
  this->greenRoutine->begin();
  this->redRoutine->begin();
}

void FeedbackLEDs::flashGreen() { this->greenRoutine->flash(); }

void FeedbackLEDs::flashRed() { this->redRoutine->flash(); }