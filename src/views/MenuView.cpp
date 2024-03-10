#include "./MenuView.h"
using namespace ace_routine;

MenuView::MenuView(State *statePtr, Screen *screenPtr,
                   SetActiveViewPtr(setActiveViewPtr))
    : BaseView(statePtr, screenPtr, setActiveViewPtr) {}

void MenuView::drawBox(int16_t x, int16_t y, String text, boolean active) {
  if (active) {
    this->canvas->fillRect(x, y, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT,
                           COLOR_GREEN_FOREGND);
    this->canvas->setTextColor(COLOR_BLACK, COLOR_GREEN_FOREGND);
  } else {
    this->canvas->drawRect(x, y, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT,
                           COLOR_GREEN_FOREGND);
    this->canvas->setTextColor(COLOR_GREEN_FOREGND, COLOR_BLACK);
  }

  int16_t x1, y1;
  uint16_t w, h;

  this->canvas->getTextBounds(text, x, y, &x1, &y1, &w, &h);

  int16_t leftPad = ceil((MENU_BUTTON_WIDTH - w) / 2);
  int16_t topPad = ceil((MENU_BUTTON_HEIGHT - h) / 2);

  this->canvas->setCursor(x + leftPad, y + topPad);
  this->canvas->print(text);
}

int MenuView::runCoroutine() {
  COROUTINE_LOOP() {
    if ((this->state->interrupt == STATE_INTR_ROTARY_BTN &&
         this->state->rotary_btn) ||
        (this->state->interrupt == STATE_INTR_MCP && this->state->mcp_record)) {
      switch (this->selectedIndex) {
      case 0:
        this->setActiveView(STATE_VIEW_RADAR);
        break;
      case 1:
        this->setActiveView(STATE_VIEW_GAMES);
        break;
      case 2:
        this->setActiveView(STATE_VIEW_LIGHTS);
        break;
      case 3:
        this->setActiveView(STATE_VIEW_SETTINGS);
        break;
      }

      COROUTINE_YIELD();
    }

    // closure for `didMove` inside a coroutine
    {
      boolean didMove = false;

      if (this->isInitialRender) {
        didMove = true;
      } else if (this->state->interrupt == STATE_INTR_ROTARY) {
        didMove = true;

        if (this->state->rotary_position >= 0) {
          this->selectedIndex = this->state->rotary_position % MENU_ITEMS_COUNT;
        } else {
          this->selectedIndex =
              abs(this->state->rotary_position % -MENU_ITEMS_COUNT);
          if (this->selectedIndex != 0) {
            this->selectedIndex = MENU_ITEMS_COUNT - this->selectedIndex;
          }
        }
      } else if (this->state->interrupt == STATE_INTR_MCP) {
        if (this->state->mcp_up && this->selectedIndex > 1) {
          didMove = true;
          this->selectedIndex -= 2;

        } else if (this->state->mcp_left && this->selectedIndex % 2 != 0) {
          didMove = true;
          this->selectedIndex -= 1;

        } else if (this->state->mcp_down && this->selectedIndex < 2) {
          didMove = true;
          this->selectedIndex += 2;

        } else if (this->state->mcp_right && this->selectedIndex % 2 == 0) {
          didMove = true;
          this->selectedIndex += 1;
        }
      }

      if (didMove) {
        this->clearMainCanvas();

        this->canvas->setTextSize(6);
        this->canvas->setTextColor(COLOR_GREEN_FOREGND, COLOR_BLACK);

        int16_t throwAway;
        uint16_t title_w, title_h;

        this->canvas->getTextBounds("MENU", 0, 0, &throwAway, &throwAway,
                                    &title_w, &title_h);

        int16_t leftPad = ceil((SCREEN_WIDTH - title_w) / 2);
        int16_t topPad = ceil((MENU_BUTTON_HEIGHT - title_h) / 2);

        this->canvas->setCursor(leftPad, MENU_BUTTON_PADDING + topPad);
        this->canvas->print("MENU");

        this->canvas->setTextSize(2);

        for (uint8_t i = 0; i < MENU_ITEMS_COUNT; i++) {
          uint8_t row = floor(i / 2);
          uint8_t col = (i % 2);

          String text;
          switch (i) {
          case 3:
            text = "Settings";
            break;
          case 2:
            text = "Lights";
            break;
          case 1:
            text = "Games";
            break;
          default:
            text = "Radar";
            break;
          }

          this->drawBox(
              (MENU_BUTTON_WIDTH * col) + (MENU_BUTTON_PADDING * (col + 1)),
              (MENU_BUTTON_HEIGHT * (row + 1)) +
                  (MENU_BUTTON_PADDING * (row + 1)) + MENU_BUTTON_PADDING,
              text, this->selectedIndex == i);
        }

        this->sendMainCanvas();
      }
    }

    COROUTINE_YIELD();
  }
}