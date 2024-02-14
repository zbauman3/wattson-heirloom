#include "./RadarView.h"
using namespace ace_routine;

int16_t movePoint(int16_t current, int16_t to, int16_t distance) {
  if (to >= current) {
    return min((int16_t)(current + distance), to);
  }
  return max(int16_t(current - distance), to);
}

RadarPing::RadarPing() {
  this->pingCurrent.x = -PING_SIZE;
  this->pingCurrent.y = -PING_SIZE;
  this->pingEnd.x = -PING_SIZE;
  this->pingEnd.y = -PING_SIZE;
  this->pingMoveAmt.x = 0;
  this->pingMoveAmt.y = 0;
}

int RadarPing::runCoroutine() {
  COROUTINE_LOOP() {
    if (this->pingCurrent.x == this->pingEnd.x &&
        this->pingCurrent.y == this->pingEnd.y) {

      if (random(0, 2) == 1) {
        this->pingCurrent.x = -PING_SIZE;
        this->pingEnd.x = SCREEN_WIDTH + PING_SIZE;

        // swap direction
        if (random(0, 2) == 1) {
          this->pingCurrent.x = this->pingCurrent.x ^ this->pingEnd.x;
          this->pingEnd.x = this->pingCurrent.x ^ this->pingEnd.x;
          this->pingCurrent.x = this->pingCurrent.x ^ this->pingEnd.x;
        }

        this->pingCurrent.y = random(PING_SIZE, SCREEN_HEIGHT - PING_SIZE);
        this->pingEnd.y = random(PING_SIZE, SCREEN_HEIGHT - PING_SIZE);
      } else {
        this->pingCurrent.y = -PING_SIZE;
        this->pingEnd.y = SCREEN_HEIGHT + PING_SIZE;

        // swap direction
        if (random(0, 2) == 1) {
          this->pingCurrent.y = this->pingCurrent.y ^ this->pingEnd.y;
          this->pingEnd.y = this->pingCurrent.y ^ this->pingEnd.y;
          this->pingCurrent.y = this->pingCurrent.y ^ this->pingEnd.y;
        }

        this->pingCurrent.x = random(PING_SIZE, SCREEN_WIDTH - PING_SIZE);
        this->pingEnd.x = random(PING_SIZE, SCREEN_WIDTH - PING_SIZE);
      }

      this->pingMoveAmt.x =
          max(int16_t(abs(this->pingCurrent.x - this->pingEnd.x) / 100),
              int16_t(1));
      this->pingMoveAmt.y =
          max(int16_t(abs(this->pingCurrent.y - this->pingEnd.y) / 100),
              int16_t(1));

      COROUTINE_DELAY_SECONDS(random(2, 10));
    } else {
      this->pingCurrent.x =
          movePoint(this->pingCurrent.x, this->pingEnd.x, this->pingMoveAmt.x);
      this->pingCurrent.y =
          movePoint(this->pingCurrent.y, this->pingEnd.y, this->pingMoveAmt.y);
      COROUTINE_DELAY(random(10, 1000));
    }
  }
}

void movePing(Coord *current, Coord *to, int16_t distance) {
  current->x = movePoint(current->x, to->x, distance);
  current->y = movePoint(current->y, to->y, distance);
}

RadarView::RadarView(State *statePtr, Screen *screenPtr,
                     SetActiveViewPtr(setActiveViewPtr))
    : BaseView(statePtr, screenPtr, setActiveViewPtr), ping1(), ping2(),
      ping3() {
  this->waveRadius = 1;
}

void RadarView::drawBackground() {
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

void RadarView::drawPingCircle(int16_t x, int16_t y) {
  this->canvas->fillCircle(x, y, PING_SIZE, 0x0903);
  this->canvas->fillCircle(x, y, PING_SIZE - 2, 0x12a7);
  this->canvas->fillCircle(x, y, PING_SIZE - 3, 0x0c0a);
}

void RadarView::drawPings() {
  this->ping1.runCoroutine();
  this->drawPingCircle(this->ping1.pingCurrent.x, this->ping1.pingCurrent.y);

  this->ping2.runCoroutine();
  this->drawPingCircle(this->ping2.pingCurrent.x, this->ping2.pingCurrent.y);

  this->ping3.runCoroutine();
  this->drawPingCircle(this->ping3.pingCurrent.x, this->ping3.pingCurrent.y);
}

void RadarView::drawWave() {
  if (this->waveRadius >= SCREEN_HEIGHT - 3) {
    this->waveRadius = 1;
  } else {
    this->waveRadius += 3;
  }

  this->canvas->drawCircle(SCREEN_CENTER_X, SCREEN_HEIGHT, this->waveRadius - 1,
                           COLOR_GREEN_FOREGND);
  this->canvas->drawCircle(SCREEN_CENTER_X, SCREEN_HEIGHT, this->waveRadius,
                           COLOR_GREEN_FOREGND);
  this->canvas->drawCircle(SCREEN_CENTER_X, SCREEN_HEIGHT, this->waveRadius + 1,
                           COLOR_GREEN_FOREGND);
}

int RadarView::runCoroutine() {
  COROUTINE_LOOP() {
    this->clearMainCanvas();
    this->drawBackground();
    this->drawPings();
    this->drawWave();
    this->sendMainCanvas();

    COROUTINE_YIELD();
  }
}