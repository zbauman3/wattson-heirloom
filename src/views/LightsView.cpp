#include "./LightsView.h"
using namespace ace_routine;

LightsView::LightsView(State *statePtr, Screen *screenPtr,
                       SetActiveViewPtr(setActiveViewPtr))
    : BaseView(statePtr, screenPtr, setActiveViewPtr) {}

int LightsView::runCoroutine() {
  COROUTINE_LOOP() {
    if (this->changeToMenu()) {
      COROUTINE_YIELD();
    }

    if (this->isInitialRender) {
      this->clearMainCanvas();

      this->canvas->setCursor(0, 0);

      this->canvas->println("Lights View");

      this->sendMainCanvas();
    }

    COROUTINE_YIELD();
  }
}