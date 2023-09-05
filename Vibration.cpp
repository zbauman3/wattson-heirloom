#include "./Macros.h"

#include "./Vibration.h"
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

Vibration::Vibration(Adafruit_MCP23X17 *mcpPtr, unsigned char vibeLeftPin,
                     unsigned char vibeRightPin) {
  this->mcp = mcpPtr;
  this->vibeLeft = vibeLeftPin;
  this->vibeRight = vibeRightPin;
}

void Vibration::begin() {
  this->mcp->pinMode(this->vibeLeft, OUTPUT);
  this->mcp->pinMode(this->vibeRight, OUTPUT);
}

void Vibration::tmp_vibrate() {
  this->mcp->digitalWrite(this->vibeLeft, HIGH);
  this->mcp->digitalWrite(this->vibeRight, HIGH);
  delay(150);
  this->mcp->digitalWrite(this->vibeLeft, LOW);
  this->mcp->digitalWrite(this->vibeRight, LOW);
}