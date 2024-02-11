#include "./RadarView.h"
using namespace ace_routine;

RadarView::RadarView(State *statePtr, Screen *screenPtr,
                     SetActiveViewPtr(setActiveViewPtr), Joystick *joystickPtr)
    : BaseView(statePtr, screenPtr, setActiveViewPtr) {
  this->joystick = joystickPtr;
}

void RadarView::setup() {
  this->canvas->setTextColor(ILI9341_DARKGREEN, ILI9341_BLACK);
  this->canvas->setTextSize(2);
  this->canvas->setTextWrap(false);
}

int RadarView::runCoroutine() {
  COROUTINE_LOOP() {
    this->joystick->runCoroutine();

    // if (this->state->hasInterrupt() && this->state->mcp_menu) {
    //   this->setActiveView(STATE_VIEW_DEBUG);
    //   COROUTINE_YIELD();
    // }

    if (this->isInitialRender || this->state->hasInterrupt() ||
        this->state->joystickChanged()) {

      this->canvas->setCursor(0, 0);

      this->canvas->printf("RadarView:\n");

      this->sendCanvas();
    }

    COROUTINE_YIELD();
  }
}