#include "./RadarView.h"
using namespace ace_routine;

RadarView::RadarView(State *statePtr, Adafruit_ILI9341 *tftPtr,
                     Joystick *joystickPtr, SetActiveViewPtr(setActiveViewPtr))
    : BaseView(statePtr, tftPtr, setActiveViewPtr) {
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

    if (this->state->hasInterrupt() && this->state->mcp_menu) {
      this->setActiveView(VIEW_DEBUG);
      COROUTINE_YIELD();
    }

    if (this->isInitialRender || this->state->hasInterrupt() ||
        this->state->joystickChanged()) {

      this->canvas->setCursor(0, 0);

      this->canvas->printf("RadarView:\n");

      this->sendCanvas();
    }

    COROUTINE_YIELD();
  }
}