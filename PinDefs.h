#ifndef PinDefs_H
#define PinDefs_H

#define PD_MCP_INPUT_PINS_LEN 10

class PinDefs {

public:
  static unsigned char joystickLR;
  static unsigned char joystickUD;
  static unsigned char neopixels;

  static unsigned char mcp_interrupts;
  static unsigned char rotary_interrupts;

  static unsigned char screenDC;
  static unsigned char screenCS;

  static unsigned char i2cSda;
  static unsigned char i2cScl;

  static unsigned char vibe;

  static unsigned char mcp_menu;
  static unsigned char mcp_up;
  static unsigned char mcp_record;
  static unsigned char mcp_left;
  static unsigned char mcp_down;
  static unsigned char mcp_right;
  static unsigned char mcp_one;
  static unsigned char mcp_two;
  static unsigned char mcp_ledGreen;
  static unsigned char mcp_ledRed;
  static unsigned char mcp_screenDimmer;
  static unsigned char mcp_power;
  static unsigned char mcp_trigger;

  static unsigned char mcpInputPinsLength;
  static unsigned char mcpInputPins[PD_MCP_INPUT_PINS_LEN];
};

#endif