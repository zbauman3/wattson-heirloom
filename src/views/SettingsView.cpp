#include "./SettingsView.h"
using namespace ace_routine;

SettingsView::SettingsView(State *statePtr, Screen *screenPtr,
                           SetActiveViewPtr(setActiveViewPtr))
    : BaseView(statePtr, screenPtr, setActiveViewPtr) {}

int SettingsView::runCoroutine() {
  COROUTINE_LOOP() {
    if (this->changeToMenu()) {
      COROUTINE_YIELD();
    }

    if (this->isInitialRender) {
      this->clearMainCanvas();

      this->canvas->setCursor(0, 0);

      this->canvas->println("Settings View");

      this->sendMainCanvas();
    }

    COROUTINE_YIELD();
  }
}