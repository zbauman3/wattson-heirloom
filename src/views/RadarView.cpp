#include "./RadarView.h"
using namespace ace_routine;

RadarView::RadarView(State *statePtr, Screen *screenPtr,
                     SetActiveViewPtr(setActiveViewPtr), Joystick *joystickPtr)
    : BaseView(statePtr, screenPtr, setActiveViewPtr) {
  this->joystick = joystickPtr;
}

void RadarView::drawRadarBackground() {
  // circles
  this->canvas->fillCircle(SCREEN_CENTER_X, SCREEN_HEIGHT, SCREEN_HEIGHT,
                           COLOR_GREEN_FOREGND);

  this->canvas->fillCircle(SCREEN_CENTER_X, SCREEN_HEIGHT, SCREEN_HEIGHT - 8,
                           COLOR_BLACK);

  this->canvas->fillCircle(SCREEN_CENTER_X, SCREEN_HEIGHT, SCREEN_HEIGHT - 60,
                           COLOR_GREEN_FOREGND);

  this->canvas->fillCircle(SCREEN_CENTER_X, SCREEN_HEIGHT, SCREEN_HEIGHT - 66,
                           COLOR_BLACK);

  this->canvas->fillCircle(SCREEN_CENTER_X, SCREEN_HEIGHT, SCREEN_HEIGHT - 120,
                           COLOR_GREEN_FOREGND);

  this->canvas->fillCircle(SCREEN_CENTER_X, SCREEN_HEIGHT, SCREEN_HEIGHT - 124,
                           COLOR_BLACK);

  this->canvas->fillCircle(SCREEN_CENTER_X, SCREEN_HEIGHT, SCREEN_HEIGHT - 180,
                           COLOR_GREEN_FOREGND);

  this->canvas->fillCircle(SCREEN_CENTER_X, SCREEN_HEIGHT, SCREEN_HEIGHT - 182,
                           COLOR_BLACK);

  // lines
  this->canvas->drawFastVLine(SCREEN_CENTER_X - 1, 0, SCREEN_HEIGHT,
                              COLOR_GREEN_FOREGND);
  this->canvas->drawFastVLine(SCREEN_CENTER_X, 0, SCREEN_HEIGHT,
                              COLOR_GREEN_FOREGND);
  this->canvas->drawFastVLine(SCREEN_CENTER_X + 1, 0, SCREEN_HEIGHT,
                              COLOR_GREEN_FOREGND);

  this->canvas->drawLine(19, 50, SCREEN_CENTER_X - 1, SCREEN_HEIGHT,
                         COLOR_GREEN_FOREGND);
  this->canvas->drawLine(20, 50, SCREEN_CENTER_X, SCREEN_HEIGHT,
                         COLOR_GREEN_FOREGND);
  this->canvas->drawLine(21, 50, SCREEN_CENTER_X + 1, SCREEN_HEIGHT,
                         COLOR_GREEN_FOREGND);

  this->canvas->drawLine(SCREEN_WIDTH - 21, 50, SCREEN_CENTER_X - 1,
                         SCREEN_HEIGHT, COLOR_GREEN_FOREGND);
  this->canvas->drawLine(SCREEN_WIDTH - 20, 50, SCREEN_CENTER_X, SCREEN_HEIGHT,
                         COLOR_GREEN_FOREGND);
  this->canvas->drawLine(SCREEN_WIDTH - 19, 50, SCREEN_CENTER_X + 1,
                         SCREEN_HEIGHT, COLOR_GREEN_FOREGND);
}

void RadarView::drawRadarPing(int16_t x, int16_t y) {
  this->canvas->fillCircle(x, y, 16, 0x0903);
  this->canvas->fillCircle(x, y, 14, 0x12a7);
  this->canvas->fillCircle(x, y, 13, 0x0c0a);
}

int RadarView::runCoroutine() {
  COROUTINE_LOOP() {
    this->joystick->runCoroutine();

    // if (this->state->hasInterrupt() && this->state->mcp_menu) {
    //   this->setActiveView(STATE_VIEW_DEBUG);
    //   COROUTINE_YIELD();
    // }

    // if (this->isInitialRender || this->state->hasInterrupt() ||
    //     this->state->joystickChanged()) {

    if (this->isInitialRender) {

      this->drawRadarBackground();
      this->drawRadarPing(SCREEN_CENTER_X, SCREEN_CENTER_Y);

      this->sendMainCanvas();
    }

    COROUTINE_YIELD();
  }
}