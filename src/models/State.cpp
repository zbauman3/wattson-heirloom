#include "./State.h"

EepromState::EepromState(Adafruit_EEPROM_I2C *eepromPtr) {
  this->eeprom = eepromPtr;

  this->lights_mode = 0;
  this->lights_brightness = 2;
  this->lights_speed = 0;
  this->lights_direction = true;
  this->lights_color = 0;
  this->lights_theme = 1;
  this->screen_theme = 0x060f;

  this->hrdwr_plug = 0;
  this->hrdwr_trigger = 0;
};

void EepromState::begin() {
  this->lights_mode = this->eeprom->read(EEPROM_LIGHTS_MODE);
  this->lights_brightness = this->eeprom->read(EEPROM_LIGHTS_BRIGHTNESS);
  this->lights_color = this->eeprom->read(EEPROM_LIGHTS_COLOR);
  this->lights_speed = this->eeprom->read(EEPROM_LIGHTS_SPEED);
  this->lights_direction = this->eeprom->read(EEPROM_LIGHTS_DIRECTION);

  this->lights_theme = this->eeprom->read(EEPROM_LIGHTS_THEME_COLOR);
  this->screen_theme = this->getThemeColorForScreen();

  this->hrdwr_plug = this->eeprom->read(EEPROM_HRDWR_PLUG);
  this->hrdwr_trigger = this->eeprom->read(EEPROM_HRDWR_TRIGGER);
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
  case EEPROM_LIGHTS_THEME_COLOR:
    this->lights_theme = value;
    this->screen_theme = this->getThemeColorForScreen();
    break;

  case EEPROM_HRDWR_PLUG:
    this->hrdwr_plug = value;
    break;
  case EEPROM_HRDWR_TRIGGER:
    this->hrdwr_trigger = value;
    break;
  }
}

void EepromState::reset() {
  this->setValue(EEPROM_LIGHTS_MODE, 0);
  this->setValue(EEPROM_LIGHTS_BRIGHTNESS, 2);
  this->setValue(EEPROM_LIGHTS_SPEED, 0);
  this->setValue(EEPROM_LIGHTS_DIRECTION, true);
  this->setValue(EEPROM_LIGHTS_COLOR, 0);
  this->setValue(EEPROM_LIGHTS_THEME_COLOR, 1);
  this->screen_theme = this->getThemeColorForScreen();

  this->setValue(EEPROM_HRDWR_PLUG, 0);
  this->setValue(EEPROM_HRDWR_TRIGGER, 0);
};

uint16_t EepromState::getThemeColorForScreen() {
  uint16_t realColor;
  switch (this->lights_theme) {
  case 1: // Green
    realColor = 0x060f;
    break;
  case 2: // Blue
    realColor = 0x4a79;
    break;
  case 3: // Cyan
    realColor = 0x07ff;
    break;
  case 4: // Magenta
    realColor = 0xf81f;
    break;
  case 5: // Yellow
    realColor = 0xd6c5;
    break;
  case 6: // White
    realColor = 0xffff;
    break;
  case 0: // Red
  default:
    realColor = 0xf9c0;
    break;
  }

  return realColor;
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
  this->mcp_plug = false;
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

  this->isInTriggerRoutine = false;
};

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
  } else if (PinDefs::mcp_plug == pin) {
    this->mcp_plug = value;
  } else if (PinDefs::mcp_trigger == pin) {
    this->mcp_trigger = value;
  }
}

void State::begin() { this->eepromState.begin(); }