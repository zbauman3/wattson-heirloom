#include <Arduino.h>

#ifndef PinDefs_H
#define PinDefs_H

#define PD_MCP_INPUT_PINS_LEN 10
#define EEPROM_ADDR 0x50

class PinDefs {

public:
  static uint8_t joystickLR;
  static uint8_t joystickUD;
  static uint8_t neopixels;

  static uint8_t mcp_interrupts;
  static uint8_t rotary_interrupts;

  static uint8_t screenDC;
  static uint8_t screenCS;

  static uint8_t i2cSda;
  static uint8_t i2cScl;

  static uint8_t vibe;

  static uint8_t mcp_menu;
  static uint8_t mcp_up;
  static uint8_t mcp_record;
  static uint8_t mcp_left;
  static uint8_t mcp_down;
  static uint8_t mcp_right;
  static uint8_t mcp_one;
  static uint8_t mcp_two;
  static uint8_t mcp_ledGreen;
  static uint8_t mcp_ledRed;
  static uint8_t mcp_screenDimmer;
  static uint8_t mcp_power;
  static uint8_t mcp_trigger;

  static uint8_t mcpInputPinsLength;
  static uint8_t mcpInputPins[PD_MCP_INPUT_PINS_LEN];
};

#endif