#include "./LightsView.h"
using namespace ace_routine;

LightsView::LightsView(State *statePtr, Screen *screenPtr,
                       SetActiveViewPtr(setActiveViewPtr),
                       LightRods *lightRodsPtr, Adafruit_EEPROM_I2C *eepromPtr)
    : BaseView(statePtr, screenPtr, setActiveViewPtr) {
  this->lightRods = lightRodsPtr;
  this->eeprom = eepromPtr;

  this->shouldRender = true;

  // navigation
  this->screen = 0;

  // config
  this->mode = 0;
  this->brightness = 2;
  this->color = 0;
  this->speed = 0;
  this->direction = true;
}

void LightsView::setup() {
  this->cursorIndex = 0;
  this->screen = 0;

  eepromToBuffer(buffer, this->eeprom->read, EEPROM_LIGHTS_MEM_START,
                 EEPROM_LIGHTS_MEM_LENGTH);

  this->mode =
      readEepromBuffer(buffer, EEPROM_LIGHTS_MEM_START, EEPROM_LIGHTS_MODE);
  this->brightness = readEepromBuffer(buffer, EEPROM_LIGHTS_MEM_START,
                                      EEPROM_LIGHTS_BRIGHTNESS);
  this->color =
      readEepromBuffer(buffer, EEPROM_LIGHTS_MEM_START, EEPROM_LIGHTS_COLOR);
  this->speed =
      readEepromBuffer(buffer, EEPROM_LIGHTS_MEM_START, EEPROM_LIGHTS_SPEED);
  this->direction = readEepromBuffer(buffer, EEPROM_LIGHTS_MEM_START,
                                     EEPROM_LIGHTS_DIRECTION);
}

void LightsView::cleanup() { this->lightRods->clear(); }

void LightsView::handleSelect() {
  switch (this->screen) {
  case 1:
    if (this->cursorIndex == 0) {
      this->screen = 0;
      this->cursorIndex = 0;
    } else {
      this->mode = this->cursorIndex - 1;
      this->eeprom->write(EEPROM_LIGHTS_MODE, this->mode);
    }
    break;
  case 2:
    if (this->cursorIndex == 0) {
      this->screen = 0;
      this->cursorIndex = 1;
    } else {
      this->brightness = this->cursorIndex - 1;
      this->eeprom->write(EEPROM_LIGHTS_BRIGHTNESS, this->brightness);
    }
    break;
  case 3:
    if (this->cursorIndex == 0) {
      this->screen = 0;
      this->cursorIndex = 2;
    } else {
      this->speed = this->cursorIndex - 1;
      this->eeprom->write(EEPROM_LIGHTS_SPEED, this->speed);
    }
    break;
  case 4:
    if (this->cursorIndex == 0) {
      this->screen = 0;
      this->cursorIndex = 3;
    } else {
      this->direction = this->cursorIndex == 2 ? false : true;
      this->eeprom->write(EEPROM_LIGHTS_DIRECTION, this->direction);
    }
    break;
  case 5:
    if (this->cursorIndex == 0) {
      this->screen = 0;
      this->cursorIndex = 2;
    } else {
      this->color = this->cursorIndex - 1;
      this->eeprom->write(EEPROM_LIGHTS_COLOR, this->color);
    }
    break;
  case 0:
  default:
    if (this->mode == 2 && this->cursorIndex == 2) {
      this->screen = 5;
    } else {
      this->screen = this->cursorIndex + 1;
    }
    this->cursorIndex = 0;
    break;
  }
}

uint8_t LightsView::getButtonCount() {
  switch (this->screen) {
  case 1:
  case 2:
  case 3:
    return 4;
  case 4:
    return 3;
  case 5:
    return 8;
  case 0:
  default:
    if (this->mode == 1) {
      return 4;
    }
    if (this->mode == 2) {
      return 3;
    }
    return 2;
  }
}

void LightsView::drawMainMenu() {
  this->drawTitle("LIGHTS");
  this->drawButton(0, this->cursorIndex == 0, "Mode");
  this->drawButton(1, this->cursorIndex == 1, "Brightness");
  if (this->mode == 1) {
    this->drawButton(2, this->cursorIndex == 2, "Speed");
    this->drawButton(3, this->cursorIndex == 3, "Direction");
  }
  if (this->mode == 2) {
    this->drawButton(2, this->cursorIndex == 2, "Color");
  }
}

void LightsView::drawModeMenu() {
  this->drawTitle("MODE");
  this->drawButton(0, this->cursorIndex == 0, "< Back");
  this->drawButton(1, this->cursorIndex == 1, "Flashlight");
  this->drawButton(2, this->cursorIndex == 2, "Rainbow");
  this->drawButton(3, this->cursorIndex == 3, "Color");
}

void LightsView::drawBrightnessMenu() {
  this->drawTitle("Brightness", true);
  this->drawButton(0, this->cursorIndex == 0, "< Back");
  this->drawButton(1, this->cursorIndex == 1, "Low");
  this->drawButton(2, this->cursorIndex == 2, "Medium");
  this->drawButton(3, this->cursorIndex == 3, "High");
}

void LightsView::drawSpeedMenu() {
  this->drawTitle("Speed");
  this->drawButton(0, this->cursorIndex == 0, "< Back");
  this->drawButton(1, this->cursorIndex == 1, "Slow");
  this->drawButton(2, this->cursorIndex == 2, "Medium");
  this->drawButton(3, this->cursorIndex == 3, "Fast");
}

void LightsView::drawDirectionMenu() {
  this->drawTitle("Direction", true);
  this->drawButton(0, this->cursorIndex == 0, "< Back");
  this->drawButton(1, this->cursorIndex == 1, "Inward");
  this->drawButton(2, this->cursorIndex == 2, "Outward");
}

void LightsView::drawColorMenu() {
  this->drawTitle("Color");
  if (this->cursorIndex <= 3) {
    this->drawButton(0, this->cursorIndex == 0, "< Back");
    this->drawButton(1, this->cursorIndex == 1, "Red");
    this->drawButton(2, this->cursorIndex == 2, "Green");
    this->drawButton(3, this->cursorIndex == 3, "Blue");
  } else {
    this->drawButton(0, this->cursorIndex == 4, "Cyan");
    this->drawButton(1, this->cursorIndex == 5, "Magenta");
    this->drawButton(2, this->cursorIndex == 6, "Yellow");
    this->drawButton(3, this->cursorIndex == 7, "White");
  }
}

int LightsView::runCoroutine() {
  COROUTINE_LOOP() {

    this->shouldRender = this->updateCursor(this->getButtonCount());

    if (!this->shouldRender && this->didSelect()) {
      this->shouldRender = true;
      this->handleSelect();
      COROUTINE_YIELD();
    }

    if (this->isInitialRender || this->shouldRender) {
      this->clearMainCanvas();

      switch (this->screen) {
      case 1:
        this->drawModeMenu();
        break;
      case 2:
        this->drawBrightnessMenu();
        break;
      case 3:
        this->drawSpeedMenu();
        break;
      case 4:
        this->drawDirectionMenu();
        break;
      case 5:
        this->drawColorMenu();
        break;
      case 0:
      default:
        this->drawMainMenu();
        break;
      }

      // closure for vars in coroutine
      {
        uint8_t realBrightness = this->brightness == 1   ? 160
                                 : this->brightness == 2 ? 240
                                                         : 75;
        uint8_t realSpeed = this->speed == 1 ? 12 : this->speed == 2 ? 3 : 25;
        uint8_t realRed, realGreen, realBlue;
        switch (this->color) {
        case 0: // Red
          realRed = 255;
          realGreen = 0;
          realBlue = 0;
          break;
        case 1: // Green
          realRed = 0;
          realGreen = 255;
          realBlue = 0;
          break;
        case 2: // Blue
          realRed = 0;
          realGreen = 0;
          realBlue = 255;
          break;
        case 3: // Cyan
          realRed = 0;
          realGreen = 255;
          realBlue = 255;
          break;
        case 4: // Magenta
          realRed = 255;
          realGreen = 0;
          realBlue = 255;
          break;
        case 5: // Yellow
          realRed = 255;
          realGreen = 255;
          realBlue = 0;
          break;
        case 6: // White
          realRed = 255;
          realGreen = 255;
          realBlue = 255;
          break;
        }

        switch (this->mode) {
        case 1:
          this->lightRods->rainbow(realBrightness, realSpeed, this->direction);
          break;
        case 2:
          this->lightRods->solid(realRed, realGreen, realBlue, realBrightness,
                                 2);
          break;
        case 0:
        default:
          this->lightRods->solid(255, 255, 255, realBrightness, 1);
          break;
        }

        this->sendMainCanvas();
      }
    }

    COROUTINE_YIELD();
  }
}