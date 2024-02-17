#include "./MenuView.h"
using namespace ace_routine;

MenuView::MenuView(State *statePtr, Screen *screenPtr,
                   SetActiveViewPtr(setActiveViewPtr))
    : BaseView(statePtr, screenPtr, setActiveViewPtr) {}

void MenuView::setup() {
  this->canvas->setTextSize(2);
  this->canvas->setTextWrap(false);
}

void MenuView::drawBox(int16_t x, int16_t y, String text, boolean active) {
  if (active) {
    this->canvas->fillRect(x, y, 145, 66, COLOR_GREEN_FOREGND);
    this->canvas->setTextColor(COLOR_BLACK, COLOR_GREEN_FOREGND);
  } else {
    this->canvas->drawRect(x, y, 145, 66, COLOR_GREEN_FOREGND);
    this->canvas->setTextColor(COLOR_GREEN_FOREGND, COLOR_BLACK);
  }

  int16_t x1, y1;
  uint16_t w, h;

  this->canvas->getTextBounds(text, x, y, &x1, &y1, &w, &h);

  int16_t leftPad = ceil((145 - w) / 2);
  int16_t topPad = ceil((66 - h) / 2);

  this->canvas->setCursor(x + leftPad, y + topPad);
  this->canvas->print(text);
}

int MenuView::runCoroutine() {
  COROUTINE_LOOP() {
    if (this->state->interrupt.type == STATE_INTR_ROTARY_BTN &&
        this->state->rotary_btn) {
      if (this->selectedIndex == 0) {
        this->setActiveView(STATE_VIEW_RADAR);
      }
      COROUTINE_YIELD();
    }

    // closure for `didMove` inside a coroutine
    {
      boolean didMove = false;

      if (this->isInitialRender) {
        didMove = true;
      } else if (this->state->interrupt.type == STATE_INTR_ROTARY) {
        didMove = true;

        if (this->state->rotary_position >= 0) {
          this->selectedIndex = this->state->rotary_position % 6;
        } else {
          this->selectedIndex = abs(this->state->rotary_position % -6);
          if (this->selectedIndex != 0) {
            this->selectedIndex = 6 - this->selectedIndex;
          }
        }
      }

      if (didMove) {
        this->clearMainCanvas();

        for (uint8_t i = 0; i < 6; i++) {
          uint8_t row = floor(i / 2);
          uint8_t col = (i % 2);

          this->drawBox((145 * col) + (10 * (col + 1)),
                        (66 * row) + (10 * (row + 1)), i == 0 ? "Radar" : "",
                        this->selectedIndex == i);
        }

        this->sendMainCanvas();
      }
    }

    COROUTINE_YIELD();
  }
}