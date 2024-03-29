#include "./PinDefs.h"

uint8_t PinDefs::joystickLR = 8;
uint8_t PinDefs::joystickUD = 9;
uint8_t PinDefs::neopixels = 17;

uint8_t PinDefs::mcp_interrupts = 6;
uint8_t PinDefs::rotary_interrupts = 7;

// using hardware pins for SPI. SCK = 36, MOSI = 36, MISO = 37 (not used)
uint8_t PinDefs::screenDC = 16;
uint8_t PinDefs::screenCS = 5;

uint8_t PinDefs::i2cSda = 41;
uint8_t PinDefs::i2cScl = 40;

uint8_t PinDefs::vibe = 18;

uint8_t PinDefs::mcp_menu = 0;
uint8_t PinDefs::mcp_up = 1;
uint8_t PinDefs::mcp_record = 2;
uint8_t PinDefs::mcp_left = 3;
uint8_t PinDefs::mcp_down = 4;
uint8_t PinDefs::mcp_right = 5;
uint8_t PinDefs::mcp_one = 6;
uint8_t PinDefs::mcp_two = 7;
uint8_t PinDefs::mcp_ledGreen = 8;
uint8_t PinDefs::mcp_ledRed = 9;
uint8_t PinDefs::mcp_plug = 10;
uint8_t PinDefs::mcp_trigger = 11;

uint8_t PinDefs::mcpInputPinsLength = PD_MCP_INPUT_PINS_LEN;
uint8_t PinDefs::mcpInputPins[PD_MCP_INPUT_PINS_LEN] = {
    PinDefs::mcp_menu,   PinDefs::mcp_up,   PinDefs::mcp_record,
    PinDefs::mcp_left,   PinDefs::mcp_down, PinDefs::mcp_right,
    PinDefs::mcp_one,    PinDefs::mcp_two,  PinDefs::mcp_plug,
    PinDefs::mcp_trigger};