#include "./Vibration.h"
#include "./Macros.h"
#include "./PinDefs.h"
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

Vibration::Vibration(Adafruit_MCP23X17 *mcpPtr) { this->mcp = mcpPtr; }

void Vibration::begin() {
  this->mcp->pinMode(PinDefs::mcp_vibeLeft, OUTPUT);
  this->mcp->pinMode(PinDefs::mcp_vibeRight, OUTPUT);
}

void Vibration::tmp_vibrate() {
  this->mcp->digitalWrite(PinDefs::mcp_vibeLeft, HIGH);
  this->mcp->digitalWrite(PinDefs::mcp_vibeRight, HIGH);
  delay(150);
  this->mcp->digitalWrite(PinDefs::mcp_vibeLeft, LOW);
  this->mcp->digitalWrite(PinDefs::mcp_vibeRight, LOW);
}