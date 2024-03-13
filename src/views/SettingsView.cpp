#include "./SettingsView.h"
using namespace ace_routine;

SettingsView::SettingsView(State *statePtr, Screen *screenPtr,
                           SetActiveViewPtr(setActiveViewPtr))
    : BaseView(statePtr, screenPtr, setActiveViewPtr) {
  this->shouldRender = false;
  this->screen = 0;
}

void SettingsView::setup() {
  this->screen = 0;
  this->cursorIndex = 0;
}

void SettingsView::handleSelect() {
  switch (this->screen) {
  case 1:
    if (this->cursorIndex == 0) {
      this->screen = 0;
      this->cursorIndex = 0;
    } else {
      this->state->eepromState.setValue(EEPROM_LIGHTS_THEME_COLOR,
                                        this->cursorIndex - 1);
    }
    break;
  case 2:
    if (this->cursorIndex == 0) {
      this->screen = 0;
      this->cursorIndex = 1;
    } else {
      this->state->eepromState.setValue(EEPROM_HRDWR_PLUG,
                                        this->cursorIndex - 1);
    }
    break;
  case 3:
    if (this->cursorIndex == 0) {
      this->screen = 0;
      this->cursorIndex = 2;
    } else {
      this->state->eepromState.setValue(EEPROM_HRDWR_TRIGGER,
                                        this->cursorIndex - 1);
    }
    break;
  case 4:
    if (this->cursorIndex == 1) {
      this->state->eepromState.reset();
    }

    this->screen = 0;
    this->cursorIndex = 0;
    break;
  case 0:
  default:
    if (this->cursorIndex == 4) {
      this->setActiveView(STATE_VIEW_DEBUG);
    } else {
      this->screen = this->cursorIndex + 1;
      this->cursorIndex = 0;
    }
    break;
  }
}

uint8_t SettingsView::getButtonCount() {
  switch (this->screen) {
  case 1:
    return 8;
  case 2:
    return 4;
  case 3:
    return 3;
  case 4:
    return 2;
  case 0:
  default:
    return 5;
  }
}

void SettingsView::drawMainMenu() {
  this->drawTitle("Settings");

  if (this->cursorIndex <= 3) {
    this->drawButton(0, this->cursorIndex == 0, "Theme Color");
    this->drawButton(1, this->cursorIndex == 1, "Override Plug");
    this->drawButton(2, this->cursorIndex == 2, "Override Trigger");
    this->drawButton(3, this->cursorIndex == 3, "Reset");
  } else {
    this->drawButton(0, this->cursorIndex == 4, "Debug Screen");
  }
}

void SettingsView::drawReset() {
  this->drawTitle("Settings > Reset Device?", 4);
  this->drawButton(0, this->cursorIndex == 0, "No");
  this->drawButton(1, this->cursorIndex == 1, "Yes");
}

void SettingsView::drawPlugOverride() {
  uint8_t selectedIndex = this->state->eepromState.hrdwr_plug + 1;

  this->drawTitle("Settings > Override Plug", 4);
  this->drawButton(0, this->cursorIndex == 0, "< Back");
  this->drawButton(
      1, (selectedIndex == 1 ? 2 : 0) + (this->cursorIndex == 1 ? 1 : 0),
      "None");
  this->drawButton(
      2, (selectedIndex == 2 ? 2 : 0) + (this->cursorIndex == 2 ? 1 : 0),
      "Plug 1");
  this->drawButton(
      3, (selectedIndex == 3 ? 2 : 0) + (this->cursorIndex == 3 ? 1 : 0),
      "Plug 2");
}

void SettingsView::drawTriggerOverride() {
  uint8_t selectedIndex = this->state->eepromState.hrdwr_trigger + 1;

  this->drawTitle("Settings > Override Trigger", 4);
  this->drawButton(0, this->cursorIndex == 0, "< Back");
  this->drawButton(
      1, (selectedIndex == 1 ? 2 : 0) + (this->cursorIndex == 1 ? 1 : 0),
      "None");
  this->drawButton(
      2, (selectedIndex == 2 ? 2 : 0) + (this->cursorIndex == 2 ? 1 : 0),
      "\"1\" Button");
}

void SettingsView::drawTheme() {
  uint8_t selectedIndex = (uint8_t)(this->state->eepromState.lights_theme) + 1;

  this->drawTitle("Settings > Theme Color", 4);
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

int SettingsView::runCoroutine() {
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
        this->drawTheme();
        break;
      case 2:
        this->drawPlugOverride();
        break;
      case 3:
        this->drawTriggerOverride();
        break;
      case 4:
        this->drawReset();
        break;
      case 0:
      default:
        this->drawMainMenu();
        break;
      }

      this->sendMainCanvas();
    }

    COROUTINE_YIELD();
  }
}