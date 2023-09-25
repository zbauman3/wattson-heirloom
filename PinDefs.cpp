#include "./PinDefs.h"

unsigned char PinDefs::joystickLR = 0;
unsigned char PinDefs::joystickUD = 1;
unsigned char PinDefs::neopixels = 3;
unsigned char PinDefs::interrupts = 4;
unsigned char PinDefs::screenDC = 20;
unsigned char PinDefs::screenCS = 21;

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
unsigned char PinDefs::mcp_vibeLeft = 13;
unsigned char PinDefs::mcp_vibeRight = 14;
unsigned char PinDefs::mcp_rotaryInt = 15;

unsigned char PinDefs::mcpInputPinsLength = PD_MCP_INPUT_PINS_LEN;
unsigned char PinDefs::mcpInputPins[PD_MCP_INPUT_PINS_LEN] = {
    PinDefs::mcp_menu,   PinDefs::mcp_up,   PinDefs::mcp_record,
    PinDefs::mcp_left,   PinDefs::mcp_down, PinDefs::mcp_right,
    PinDefs::mcp_one,    PinDefs::mcp_two,  PinDefs::mcp_power,
    PinDefs::mcp_trigger};