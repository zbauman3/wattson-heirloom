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

void Vibration::begin() { this->mcp->pinMode(PinDefs::mcp_vibe, OUTPUT); }

int Vibration::runCoroutine() {
  COROUTINE_BEGIN();
  if (this->routine == 1) {
    this->mcp->digitalWrite(PinDefs::mcp_vibe, LOW);

    for (this->routineLoop = 1; this->routineLoop <= 10; this->routineLoop++) {
      if (this->routineLoop % 2 == 0) {
        this->mcp->digitalWrite(PinDefs::mcp_vibe, HIGH);
      } else {
        this->mcp->digitalWrite(PinDefs::mcp_vibe, LOW);
      }

      float percent = this->routineLoop / float(10);
      COROUTINE_DELAY(char(650 - (500 / percent)));
    }

    this->mcp->digitalWrite(PinDefs::mcp_vibe, HIGH);
    COROUTINE_DELAY(500);
    this->mcp->digitalWrite(PinDefs::mcp_vibe, LOW);
  }

  this->routine = 0;

  COROUTINE_END();
}

void Vibration::startPattern(unsigned char which) {
  if (which <= 0 || which > 1) {
    return;
  }

  this->routine = which;
  this->reset();
}