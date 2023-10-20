#include "./PinDefs.h"

unsigned char PinDefs::joystickLR = 8; // 0 - 8
unsigned char PinDefs::joystickUD = 9; // 1 - 9
unsigned char PinDefs::neopixels = 17; // 3 - 17

unsigned char PinDefs::mcp_interrupts = 18;   // 4 - 18
unsigned char PinDefs::rotary_interrupts = 7; // X - 7

unsigned char PinDefs::screenDC = 16; // 20 - 16
unsigned char PinDefs::screenCS = 5;  // 21 - 5

unsigned char PinDefs::i2cSda = 41;
unsigned char PinDefs::i2cScl = 40;

unsigned char PinDefs::mcp_menu = 0;
unsigned char PinDefs::mcp_up = 1;
unsigned char PinDefs::mcp_record = 2;
unsigned char PinDefs::mcp_left = 3;
unsigned char PinDefs::mcp_down = 4;
unsigned char PinDefs::mcp_right = 5;
unsigned char PinDefs::mcp_one = 6;
unsigned char PinDefs::mcp_two = 7;
unsigned char PinDefs::mcp_ledGreen = 8;
unsigned char PinDefs::mcp_ledRed = 9;
unsigned char PinDefs::mcp_power = 10;
unsigned char PinDefs::mcp_trigger = 11;
unsigned char PinDefs::mcp_screenDimmer = 12;
unsigned char PinDefs::mcp_vibe = 13;

unsigned char PinDefs::mcpInputPinsLength = PD_MCP_INPUT_PINS_LEN;
unsigned char PinDefs::mcpInputPins[PD_MCP_INPUT_PINS_LEN] = {
    PinDefs::mcp_menu,   PinDefs::mcp_up,   PinDefs::mcp_record,
    PinDefs::mcp_left,   PinDefs::mcp_down, PinDefs::mcp_right,
    PinDefs::mcp_one,    PinDefs::mcp_two,  PinDefs::mcp_power,
    PinDefs::mcp_trigger};