#include <Arduino.h>

#ifndef State_H
#define State_H

#define STATE_INTR_EMPTY 0x00
#define STATE_INTR_MCP 0x01
#define STATE_INTR_ROTARY 0x02
#define STATE_INTR_ROTARY_BTN 0x03

typedef struct {
  unsigned char type;
  union {
    unsigned char mcp;
    signed long rotary;
    bool rotaryPressed;
  };
} interruptState;

class State {
public:
  State();

  interruptState interrupt;

  bool hasInterrupt();
};

#endif