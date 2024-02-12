#include "./RadarView.h"
using namespace ace_routine;

int16_t movePoint(int16_t current, int16_t to, int16_t percentStep) {
  int16_t pMove = ceil(abs(current - to) / percentStep);
  int16_t newCurrent;

  if (to >= current) {
    newCurrent = min((int16_t)(current + pMove), to);
  } else {
    newCurrent = max(int16_t(current - pMove), to);
  }

  return newCurrent;
}

void movePing(Coord *current, Coord *to, int16_t percentStep) {
  int16_t newY = floor(current->y - to->y);
  int16_t newC = floor(current->x - to->x);

  current->x = movePoint(current->x, to->x, percentStep);
  current->y = movePoint(current->y, to->y, percentStep);
}

RadarView::RadarView(State *statePtr, Screen *screenPtr,
                     SetActiveViewPtr(setActiveViewPtr))
    : BaseView(statePtr, screenPtr, setActiveViewPtr) {
  this->pingCurrent.x = 0;
  this->pingCurrent.y = 0;
  this->pingEnd.x = 0;
  this->pingEnd.y = 0;
}

void RadarView::setup() {
  this->pingCurrent.x = 0;
  this->pingCurrent.y = 0;
  this->pingEnd.x = SCREEN_WIDTH;
  this->pingEnd.y = SCREEN_HEIGHT;
}

void RadarView::moveRadarPing() {
  movePing(&this->pingCurrent, &this->pingEnd, 10);
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
    // if (this->state->hasInterrupt() && this->state->mcp_menu) {
    //   this->setActiveView(STATE_VIEW_DEBUG);
    //   COROUTINE_YIELD();
    // }

    // if (this->isInitialRender || this->state->hasInterrupt() ||
    //     this->state->joystickChanged()) {

    this->clearMainCanvas();
    this->drawRadarBackground();
    this->moveRadarPing();
    this->drawRadarPing(this->pingCurrent.x, this->pingCurrent.y);
    this->sendMainCanvas();

    COROUTINE_DELAY(250);
    // COROUTINE_YIELD();
  }
}