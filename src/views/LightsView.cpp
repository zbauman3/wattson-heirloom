#include "./LightsView.h"
using namespace ace_routine;

LightsView::LightsView(State *statePtr, Screen *screenPtr,
                       SetActiveViewPtr(setActiveViewPtr),
                       LightRods *lightRodsPtr)
    : BaseView(statePtr, screenPtr, setActiveViewPtr) {
  this->lightRods = lightRodsPtr;
  this->shouldRender = true;
  this->screen = 0;
}

void LightsView::setup() {
  this->cursorIndex = 0;
  this->screen = 0;
}

void LightsView::cleanup() { this->lightRods->clear(); }

void LightsView::handleSelect() {
  switch (this->screen) {
  case 1:
    if (this->cursorIndex == 0) {
      this->screen = 0;
      this->cursorIndex = 0;
    } else {
      this->state->eepromState.setValue(EEPROM_LIGHTS_MODE,
                                        this->cursorIndex - 1);
    }
    break;
  case 2:
    if (this->cursorIndex == 0) {
      this->screen = 0;
      this->cursorIndex = 1;
    } else {
      this->state->eepromState.setValue(EEPROM_LIGHTS_BRIGHTNESS,
                                        this->cursorIndex - 1);
    }
    break;
  case 3:
    if (this->cursorIndex == 0) {
      this->screen = 0;
      this->cursorIndex = 2;
    } else {
      this->state->eepromState.setValue(EEPROM_LIGHTS_SPEED,
                                        this->cursorIndex - 1);
    }
    break;
  case 4:
    if (this->cursorIndex == 0) {
      this->screen = 0;
      this->cursorIndex = 3;
    } else {
      this->state->eepromState.setValue(EEPROM_LIGHTS_DIRECTION,
                                        this->cursorIndex == 2 ? false : true);
    }
    break;
  case 5:
    if (this->cursorIndex == 0) {
      this->screen = 0;
      this->cursorIndex = 2;
    } else {
      this->state->eepromState.setValue(EEPROM_LIGHTS_COLOR,
                                        this->cursorIndex - 1);
    }
    break;
  case 0:
  default:
    if (this->state->eepromState.lights_mode == 2 && this->cursorIndex == 2) {
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
    if (this->state->eepromState.lights_mode == 1) {
      return 4;
    }
    if (this->state->eepromState.lights_mode == 2) {
      return 3;
    }
    return 2;
  }
}

void LightsView::drawMainMenu() {
  this->drawTitle("Lights");
  this->drawButton(0, this->cursorIndex == 0, "Mode");
  this->drawButton(1, this->cursorIndex == 1, "Brightness");
  if (this->state->eepromState.lights_mode == 1) {
    this->drawButton(2, this->cursorIndex == 2, "Speed");
    this->drawButton(3, this->cursorIndex == 3, "Direction");
  }
  if (this->state->eepromState.lights_mode == 2) {
    this->drawButton(2, this->cursorIndex == 2, "Color");
  }
}

void LightsView::drawModeMenu() {
  uint8_t selectedIndex = this->state->eepromState.lights_mode + 1;

  this->drawTitle("Lights > Mode", 4);
  this->drawButton(0, this->cursorIndex == 0, "< Back");
  this->drawButton(
      1, (selectedIndex == 1 ? 2 : 0) + (this->cursorIndex == 1 ? 1 : 0),
      "Flashlight");
  this->drawButton(
      2, (selectedIndex == 2 ? 2 : 0) + (this->cursorIndex == 2 ? 1 : 0),
      "Rainbow");
  this->drawButton(
      3, (selectedIndex == 3 ? 2 : 0) + (this->cursorIndex == 3 ? 1 : 0),
      "Color");
}

void LightsView::drawBrightnessMenu() {
  uint8_t selectedIndex = this->state->eepromState.lights_brightness + 1;

  this->drawTitle("Lights > Brightness", 4);
  this->drawButton(0, this->cursorIndex == 0, "< Back");
  this->drawButton(
      1, (selectedIndex == 1 ? 2 : 0) + (this->cursorIndex == 1 ? 1 : 0),
      "Low");
  this->drawButton(
      2, (selectedIndex == 2 ? 2 : 0) + (this->cursorIndex == 2 ? 1 : 0),
      "Medium");
  this->drawButton(
      3, (selectedIndex == 3 ? 2 : 0) + (this->cursorIndex == 3 ? 1 : 0),
      "High");
}

void LightsView::drawSpeedMenu() {
  uint8_t selectedIndex = this->state->eepromState.lights_speed + 1;

  this->drawTitle("Lights > Speed", 4);
  this->drawButton(0, this->cursorIndex == 0, "< Back");
  this->drawButton(
      1, (selectedIndex == 1 ? 2 : 0) + (this->cursorIndex == 1 ? 1 : 0),
      "Slow");
  this->drawButton(
      2, (selectedIndex == 2 ? 2 : 0) + (this->cursorIndex == 2 ? 1 : 0),
      "Medium");
  this->drawButton(
      3, (selectedIndex == 3 ? 2 : 0) + (this->cursorIndex == 3 ? 1 : 0),
      "Fast");
}

void LightsView::drawDirectionMenu() {
  uint8_t selectedIndex = this->state->eepromState.lights_direction ? 1 : 2;

  this->drawTitle("Lights > Direction", 4);
  this->drawButton(0, this->cursorIndex == 0, "< Back");
  this->drawButton(
      1, (selectedIndex == 1 ? 2 : 0) + (this->cursorIndex == 1 ? 1 : 0),
      "Inward");
  this->drawButton(
      2, (selectedIndex == 2 ? 2 : 0) + (this->cursorIndex == 2 ? 1 : 0),
      "Outward");
}

void LightsView::drawColorMenu() {
  uint8_t selectedIndex = (uint8_t)(this->state->eepromState.lights_color) + 1;

  this->drawTitle("Lights > Color", 4);
  if (this->cursorIndex <= 3) {
    this->drawButton(0, this->cursorIndex == 0, "< Back");
    this->drawButton(
        1, (selectedIndex == 1 ? 2 : 0) + (this->cursorIndex == 1 ? 1 : 0),
        "Red");
    this->drawButton(
        2, (selectedIndex == 2 ? 2 : 0) + (this->cursorIndex == 2 ? 1 : 0),
        "Green");
    this->drawButton(
        3, (selectedIndex == 3 ? 2 : 0) + (this->cursorIndex == 3 ? 1 : 0),
        "Blue");
  } else {
    this->drawButton(
        0, (selectedIndex == 4 ? 2 : 0) + (this->cursorIndex == 4 ? 1 : 0),
        "Cyan");
    this->drawButton(
        1, (selectedIndex == 5 ? 2 : 0) + (this->cursorIndex == 5 ? 1 : 0),
        "Magenta");
    this->drawButton(
        2, (selectedIndex == 6 ? 2 : 0) + (this->cursorIndex == 6 ? 1 : 0),
        "Yellow");
    this->drawButton(
        3, (selectedIndex == 7 ? 2 : 0) + (this->cursorIndex == 7 ? 1 : 0),
        "White");
  }
}

int LightsView::runCoroutine() {
  COROUTINE_LOOP() {

    this->shouldRender = this->updateCursor(this->getButtonCount());

    if (!this->shouldRender && this->didSelect()) {
      this->shouldRender = true;
      this->handleSelect();
      COROUTINE_DELAY(10);
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
        uint8_t realBrightness =
            this->state->eepromState.lights_brightness == 1   ? 160
            : this->state->eepromState.lights_brightness == 2 ? 240
                                                              : 75;
        uint8_t realSpeed = this->state->eepromState.lights_speed == 1   ? 12
                            : this->state->eepromState.lights_speed == 2 ? 3
                                                                         : 25;
        uint8_t realRed, realGreen, realBlue;
        switch (this->state->eepromState.lights_color) {
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
        case 0: // Red
        default:
          realRed = 255;
          realGreen = 0;
          realBlue = 0;
          break;
        }

        switch (this->state->eepromState.lights_mode) {
        case 1:
          this->lightRods->rainbow(realBrightness, realSpeed,
                                   this->state->eepromState.lights_direction);
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