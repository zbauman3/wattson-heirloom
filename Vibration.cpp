#include "./Vibration.h"
#include "./Macros.h"
#include "./PinDefs.h"
#include <AceRoutine.h>
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>
using namespace ace_routine;

Vibration::Vibration(Adafruit_MCP23X17 *mcpPtr) {
  this->mcp = mcpPtr;
  this->routine = 0;
}

void Vibration::begin() {
  this->mcp->pinMode(PinDefs::mcp_vibeLeft, OUTPUT);
  this->mcp->pinMode(PinDefs::mcp_vibeRight, OUTPUT);
}

int Vibration::runCoroutine() {
  COROUTINE_BEGIN();

  if (this->routine == 1) {
    this->mcp->digitalWrite(PinDefs::mcp_vibeLeft, HIGH);
    this->mcp->digitalWrite(PinDefs::mcp_vibeRight, HIGH);
    COROUTINE_DELAY(150);
    this->mcp->digitalWrite(PinDefs::mcp_vibeLeft, LOW);
    this->mcp->digitalWrite(PinDefs::mcp_vibeRight, LOW);
  }

  this->routine = 0;

  COROUTINE_END();
}

void Vibration::tmp_vibrate() {
  this->routine = 1;
  this->reset();
}