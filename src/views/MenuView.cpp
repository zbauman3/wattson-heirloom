#include "./MenuView.h"
using namespace ace_routine;

MenuView::MenuView(State *statePtr, Screen *screenPtr,
                   SetActiveViewPtr(setActiveViewPtr))
    : BaseView(statePtr, screenPtr, setActiveViewPtr) {}

int MenuView::runCoroutine() {
  COROUTINE_LOOP() {
    if (this->didSelect()) {
      switch (this->cursorIndex) {
      case 0:
        this->setActiveView(STATE_VIEW_RADAR);
        break;
      // case 1:
      //   this->setActiveView(STATE_VIEW_GAMES);
      //   break;
      case 1:
        this->setActiveView(STATE_VIEW_LIGHTS);
        break;
      case 2:
        this->setActiveView(STATE_VIEW_SETTINGS);
        break;
      }

      COROUTINE_YIELD();
    }

    // closure for `didMove` inside a coroutine
    {
      bool didMove = this->updateCursor(MENU_VIEW_ITEMS);

      if (didMove || this->isInitialRender) {
        this->clearMainCanvas();
        this->drawTitle("MENU");
        this->canvas->setTextSize(2);

        for (uint8_t i = 0; i < MENU_VIEW_ITEMS; i++) {
          String text;
          switch (i) {
          case 2:
            text = "Settings";
            break;
          case 1:
            text = "Lights";
            break;
          // case 1:
          //   text = "Games";
          //   break;
          default:
            text = "Radar";
            break;
          }

          this->drawButton(i, this->cursorIndex == i, text);
        }

        this->sendMainCanvas();
      }
    }

    COROUTINE_YIELD();
  }
}