#include "./State.h"

EepromState::EepromState(Adafruit_EEPROM_I2C *eepromPtr) {
  this->eeprom = eepromPtr;
};

void EepromState::begin() {
  eepromToBuffer(buffer, this->eeprom->read, EEPROM_LIGHTS_MEM_START,
                 EEPROM_LIGHTS_MEM_LENGTH);

  this->lights_mode =
      readEepromBuffer(buffer, EEPROM_LIGHTS_MEM_START, EEPROM_LIGHTS_MODE);
  this->lights_brightness = readEepromBuffer(buffer, EEPROM_LIGHTS_MEM_START,
                                             EEPROM_LIGHTS_BRIGHTNESS);
  this->lights_color =
      readEepromBuffer(buffer, EEPROM_LIGHTS_MEM_START, EEPROM_LIGHTS_COLOR);
  this->lights_speed =
      readEepromBuffer(buffer, EEPROM_LIGHTS_MEM_START, EEPROM_LIGHTS_SPEED);
  this->lights_direction = readEepromBuffer(buffer, EEPROM_LIGHTS_MEM_START,
                                            EEPROM_LIGHTS_DIRECTION);
}

void EepromState::setValue(uint16_t addr, uint8_t value) {
  this->eeprom->write(addr, value);

  switch (addr) {
  case EEPROM_LIGHTS_MODE:
    this->lights_mode = value;
    break;
  case EEPROM_LIGHTS_BRIGHTNESS:
    this->lights_brightness = value;
    break;
  case EEPROM_LIGHTS_SPEED:
    this->lights_speed = value;
    break;
  case EEPROM_LIGHTS_DIRECTION:
    this->lights_direction = value;
    break;
  case EEPROM_LIGHTS_COLOR:
    this->lights_color = value;
    break;
  }
}

State::State(Adafruit_EEPROM_I2C *eepromPtr) : eepromState(eepromPtr) {
  this->mcp_menu = false;
  this->mcp_up = false;
  this->mcp_record = false;
  this->mcp_left = false;
  this->mcp_down = false;
  this->mcp_right = false;
  this->mcp_one = false;
  this->mcp_two = false;
  this->mcp_power = false;
  this->mcp_trigger = false;
  this->rotary_btn = false;
  this->rotary_position = 0;
  this->rotary_direction = 0;

  this->interrupt = STATE_INTR_EMPTY;
  this->joystick_lr = 0;
  this->joystick_ud = 0;
  this->joystick_lr_prev = 0;
  this->joystick_ud_prev = 0;

  this->activeView = STATE_VIEW_INIT;
  this->viewChanged = true;
};

bool State::hasInterrupt() { return this->interrupt != STATE_INTR_EMPTY; };

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

void State::setMcpValueByPin(uint8_t pin, bool value) {
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

void State::begin() { this->eepromState.begin(); }