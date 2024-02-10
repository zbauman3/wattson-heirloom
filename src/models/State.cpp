#include "./State.h"

State::State() {
  this->interrupt = {.type = STATE_INTR_EMPTY};
  this->joystick_lr = 0;
  this->joystick_ud = 0;
  this->joystick_lr_prev = 0;
  this->joystick_ud_prev = 0;
};

bool State::hasInterrupt() { return this->interrupt.type != STATE_INTR_EMPTY; };

// outside of dead zone
bool State::joystickMoving() {
  return this->joystick_lr < 130 || this->joystick_lr > 190 ||
         this->joystick_ud < 130 || this->joystick_ud > 190;
}

bool State::joystickChanged() {
  return this->joystickMoving() ||
         abs(this->joystick_lr_prev - this->joystick_lr) > 2 ||
         abs(this->joystick_ud_prev - this->joystick_ud) > 2;
}

void State::setJoystick(uint8_t _joystick_lr, uint8_t _joystick_ud) {
  this->joystick_lr_prev = this->joystick_lr;
  this->joystick_ud_prev = this->joystick_ud;

  this->joystick_lr = _joystick_lr;
  this->joystick_ud = _joystick_ud;
}

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
