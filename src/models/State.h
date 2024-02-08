#include "../config/PinDefs.h"
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
  bool mcp_menu;
  bool mcp_up;
  bool mcp_record;
  bool mcp_left;
  bool mcp_down;
  bool mcp_right;
  bool mcp_one;
  bool mcp_two;
  bool mcp_power;
  bool mcp_trigger;

  bool rotary_btn;
  signed long rotary_position;

  unsigned char screenBrightness;

  unsigned char joystick_ud;
  unsigned char joystick_lr;

  interruptState interrupt;

  State();
  bool hasInterrupt();
  void setMcpValueByPin(unsigned char pin, bool value);
};

#endif