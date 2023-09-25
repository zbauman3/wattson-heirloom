#ifndef PinDefs_H
#define PinDefs_H

#define PD_MCP_INPUT_PINS_LEN 10

class PinDefs {

public:
  static unsigned char joystickLR;
  static unsigned char joystickUD;
  static unsigned char neopixels;
  static unsigned char interrupts;
  static unsigned char screenDC;
  static unsigned char screenCS;

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
  static unsigned char mcp_vibeLeft;
  static unsigned char mcp_vibeRight;
  static unsigned char mcp_power;
  static unsigned char mcp_trigger;
  static unsigned char mcp_rotaryInt;

  static unsigned char mcpInputPinsLength;
  static unsigned char mcpInputPins[PD_MCP_INPUT_PINS_LEN];
};

#endif