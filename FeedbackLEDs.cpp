#include "./FeedbackLEDs.h"
#include "./PinDefs.h"
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

FeedbackLEDs::FeedbackLEDs(Adafruit_MCP23X17 *mcpPtr) { this->mcp = mcpPtr; }

void FeedbackLEDs::begin() {
  this->mcp->pinMode(PinDefs::mcp_ledRed, OUTPUT);
  this->mcp->pinMode(PinDefs::mcp_ledGreen, OUTPUT);

  this->set(PinDefs::mcp_ledRed, LOW);
  this->set(PinDefs::mcp_ledGreen, LOW);
}

void FeedbackLEDs::set(unsigned char which, unsigned char state) {
  this->mcp->digitalWrite(which, state);
}

void FeedbackLEDs::setRed(unsigned char state) {
  this->set(PinDefs::mcp_ledRed, state);
}

void FeedbackLEDs::setGreen(unsigned char state) {
  this->set(PinDefs::mcp_ledGreen, state);
}