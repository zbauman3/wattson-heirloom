#include "../config/PinDefs.h"
#include <Arduino.h>

#ifndef State_H
#define State_H

#define STATE_INTR_EMPTY 0x00
#define STATE_INTR_MCP 0x01
#define STATE_INTR_ROTARY 0x02
#define STATE_INTR_ROTARY_BTN 0x03

#define STATE_VIEW_DEBUG 0x00
#define STATE_VIEW_RADAR 0x01
#define STATE_VIEW_MENU 0x02

// #define STATE_VIEW_INIT STATE_VIEW_RADAR
#define STATE_VIEW_INIT STATE_VIEW_MENU

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

  unsigned char joystick_lr_prev;
  unsigned char joystick_ud_prev;
  unsigned char joystick_lr;
  unsigned char joystick_ud;

  uint8_t activeView;
  bool viewChanged;

  uint8_t interrupt;

  State();

  bool hasInterrupt();
  void setJoystick(uint8_t joystick_lr, uint8_t joystick_ud);
  bool joystickMoving();
  bool joystickChanged();
  void setMcpValueByPin(unsigned char pin, bool value);
};

#endif