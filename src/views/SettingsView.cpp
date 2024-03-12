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
      this->state->eepromState.setValue(EEPROM_HRDWR_PLUG,
                                        this->cursorIndex - 1);
    }
    break;
  case 2:
    if (this->cursorIndex == 1) {
      this->state->eepromState.reset();
    }

    this->screen = 0;
    this->cursorIndex = 0;
    break;
  case 0:
  default:
    if (this->cursorIndex == 2) {
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
    return 4;
  case 2:
    return 2;
  case 0:
  default:
    return 3;
  }
}

void SettingsView::drawMainMenu() {
  this->drawTitle("Settings");

  this->drawButton(0, this->cursorIndex == 0, "Override Plug");
  this->drawButton(1, this->cursorIndex == 1, "Reset");
  this->drawButton(2, this->cursorIndex == 2, "Debug Screen");
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
      2, (selectedIndex == 2 ? 2 : 0) + (this->cursorIndex == 2 ? 1 : 0), "1");
  this->drawButton(
      3, (selectedIndex == 3 ? 2 : 0) + (this->cursorIndex == 3 ? 1 : 0), "2");
}

int SettingsView::runCoroutine() {
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
        this->drawPlugOverride();
        break;
      case 2:
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