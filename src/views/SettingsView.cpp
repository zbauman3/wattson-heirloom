#include "./SettingsView.h"
using namespace ace_routine;

SettingsView::SettingsView(State *statePtr, Screen *screenPtr,
                           SetActiveViewPtr(setActiveViewPtr))
    : BaseView(statePtr, screenPtr, setActiveViewPtr) {

  this->shouldRender = false;
  this->screen = 0;
}

void SettingsView::setup() {}

void SettingsView::handleSelect() {
  switch (this->screen) {
  case 0:
  default:
    if (this->cursorIndex == 0) {
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
  case 0:
  default:
    return 3;
  }
}

void SettingsView::drawMainMenu() {
  this->drawTitle("SETTINGS");

  this->drawButton(0, this->cursorIndex == 0, "Debug Screen");
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