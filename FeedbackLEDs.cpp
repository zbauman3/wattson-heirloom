#include "./FeedbackLEDs.h"
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

Z_FeedbackLEDs::Z_FeedbackLEDs(Adafruit_MCP23X17 *mcpPtr, unsigned char redPin,
                               unsigned char greenPin) {
  this->mcp = mcpPtr;
  this->red = {.pin = redPin, .state = LOW};
  this->green = {.pin = greenPin, .state = LOW};
}

void Z_FeedbackLEDs::begin() {
  this->mcp->pinMode(this->red.pin, OUTPUT);
  this->mcp->pinMode(this->green.pin, OUTPUT);

  this->off(FEEDBACK_RED);
  this->off(FEEDBACK_GREEN);
}

feedbackLed *Z_FeedbackLEDs::colorCodeToFeedbackLed(unsigned char colorCode) {
  switch (colorCode) {
  case FEEDBACK_RED:
    return &(this->red);
  case FEEDBACK_GREEN:
  default:
    return &(this->green);
  }
}

void Z_FeedbackLEDs::set(feedbackLed *led, unsigned char state) {
  led->state = state;
  this->mcp->digitalWrite(led->pin, led->state);
}

void Z_FeedbackLEDs::on(unsigned char colorCode) {
  this->set(this->colorCodeToFeedbackLed(colorCode), HIGH);
}
void Z_FeedbackLEDs::off(unsigned char colorCode) {
  this->set(this->colorCodeToFeedbackLed(colorCode), LOW);
}