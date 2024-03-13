#include "./GamesView.h"
using namespace ace_routine;

// UNUSED :(

GamesView::GamesView(State *statePtr, Screen *screenPtr,
                     SetActiveViewPtr(setActiveViewPtr))
    : BaseView(statePtr, screenPtr, setActiveViewPtr) {}

int GamesView::runCoroutine() {
  COROUTINE_LOOP() {

    if (this->isInitialRender) {
      this->clearMainCanvas();

      this->canvas->setCursor(0, 0);

      this->canvas->println("Games View");

      this->sendMainCanvas();
    }

    COROUTINE_YIELD();
  }
}