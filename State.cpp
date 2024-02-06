#include "./State.h"

State::State() { this->interrupt = {.type = STATE_INTR_EMPTY}; };

bool State::hasInterrupt() { return this->interrupt.type != STATE_INTR_EMPTY; };

void State::setMcpValueByPin(unsigned char pin, bool value) {
  if (PinDefs::mcp_menu == pin) {
    this->mcp_menu = value;
  } else if (PinDefs::mcp_up == pin) {
    this->mcp_up = value;
  } else if (PinDefs::mcp_record == pin) {
    this->mcp_record = value;
  } else if (PinDefs::mcp_left == pin) {
    this->mcp_left = value;
  } else if (PinDefs::mcp_down == pin) {
    this->mcp_down = value;
  } else if (PinDefs::mcp_right == pin) {
    this->mcp_right = value;
  } else if (PinDefs::mcp_one == pin) {
    this->mcp_one = value;
  } else if (PinDefs::mcp_two == pin) {
    this->mcp_two = value;
  } else if (PinDefs::mcp_power == pin) {
    this->mcp_power = value;
  } else if (PinDefs::mcp_trigger == pin) {
    this->mcp_trigger = value;
  }
}