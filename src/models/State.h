#include "../config/PinDefs.h"
#include <Arduino.h>

#ifndef State_H
#define State_H

#define STATE_INTR_EMPTY 0x00
#define STATE_INTR_MCP 0x01
#define STATE_INTR_ROTARY 0x02
#define STATE_INTR_ROTARY_BTN 0x03

#define STATE_VIEW_DEBUG 0x00
#define STATE_VIEW_MENU 0x01
#define STATE_VIEW_RADAR 0x02
#define STATE_VIEW_GAMES 0x03
#define STATE_VIEW_LIGHTS 0x04
#define STATE_VIEW_SETTINGS 0x05

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
  int32_t rotary_position;
  // `-1` = down
  // `0` = none
  // `1` = up
  uint8_t rotary_direction;

  uint8_t joystick_lr_prev;
  uint8_t joystick_ud_prev;
  uint8_t joystick_lr;
  uint8_t joystick_ud;

  uint8_t activeView;
  bool viewChanged;

  uint8_t interrupt;

  State();

  bool hasInterrupt();
  void setJoystick(uint8_t joystick_lr, uint8_t joystick_ud);
  bool joystickMoving();
  bool joystickChanged();
  void setMcpValueByPin(uint8_t pin, bool value);
};

#endif