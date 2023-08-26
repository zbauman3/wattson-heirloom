#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#ifndef Z_FeedbackLEDs_H
#define Z_FeedbackLEDs_H

#define FEEDBACK_RED 0x0
#define FEEDBACK_GREEN 0x1

typedef struct {
  unsigned char pin;
  unsigned char state;
} feedbackLed;

class Z_FeedbackLEDs {
private:
  Adafruit_MCP23X17 *mcp;
  feedbackLed red;
  feedbackLed green;

  feedbackLed *colorCodeToFeedbackLed(unsigned char colorCode);
  void set(feedbackLed *led, unsigned char state);

public:
  Z_FeedbackLEDs(Adafruit_MCP23X17 *mcpPtr, unsigned char redPin,
                 unsigned char greenPin);
  void begin();

  void on(unsigned char colorCode);
  void off(unsigned char colorCode);
};

#endif