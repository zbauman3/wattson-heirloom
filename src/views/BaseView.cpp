#include "./BaseView.h"

GFXcanvas16 globalCanvas(SCREEN_WIDTH, SCREEN_HEIGHT);

BaseView::BaseView(State *statePtr, Screen *screenPtr,
                   SetActiveViewPtr(setActiveViewPtr)) {
  this->state = statePtr;
  this->screen = screenPtr;
  this->canvas = &globalCanvas;
  this->isInitialRender = true;
  this->_setActiveView = setActiveViewPtr;

  // navigation
  this->cursorIndex = 0;
}

void BaseView::sendCanvas(GFXcanvas16 *newCanvas, int16_t x, int16_t y,
                          int16_t w, int16_t h) {
  this->screen->tft.drawRGBBitmap(x, y, newCanvas->getBuffer(), w, h);
}

void BaseView::sendMainCanvas() {
  this->sendCanvas(this->canvas, 0, 0, this->canvas->width(),
                   this->canvas->height());
}

void BaseView::setActiveView(uint8_t view) { this->_setActiveView(view); }

void BaseView::loop(bool _isInitialRender) {
  this->isInitialRender = _isInitialRender;

  if (_isInitialRender) {
    this->reset();
    this->clearMainCanvas();
    this->setup();
  }

  this->runCoroutine();

  if (_isInitialRender) {
    this->isInitialRender = false;
  }
}

void BaseView::clearMainCanvas() { this->canvas->fillScreen(ILI9341_BLACK); }

// this should be overriden
void BaseView::setup() {
  this->canvas->setTextSize(2);
  this->canvas->setTextWrap(false);
  this->canvas->setTextColor(COLOR_GREEN_FOREGND, COLOR_BLACK);
};

// this should be overriden
void BaseView::cleanup(){};

void BaseView::drawTitle(String title, bool small) {
  this->canvas->setTextSize(small ? 4 : 6);
  this->canvas->setTextColor(COLOR_GREEN_FOREGND, COLOR_BLACK);

  int16_t throwAway;
  uint16_t title_w;

  this->canvas->getTextBounds(title, 0, 0, &throwAway, &throwAway, &title_w,
                              (uint16_t *)&throwAway);

  int16_t leftPad = ceil((SCREEN_WIDTH - title_w) / 2);

  this->canvas->setCursor(leftPad, small ? VIEW_PADDING + 5 : VIEW_PADDING);
  this->canvas->print(title);
}

void BaseView::drawButton(uint8_t position, uint8_t selectedMode, String text) {
  this->canvas->setTextSize(2);
  this->canvas->setTextWrap(false);
  this->canvas->setCursor(0, 0);

  int16_t x = VIEW_PADDING;
  int16_t y = VIEW_TITLE_SPACE + ((VIEW_PADDING + VIEW_BUTTON_H) * position);

  if (selectedMode == 2) {
    this->canvas->drawRect(x, y, VIEW_BUTTON_W, VIEW_BUTTON_H,
                           COLOR_GREEN_FADED);
    this->canvas->setTextColor(COLOR_GREEN_FADED, COLOR_BLACK);
  } else if (selectedMode == 1) {
    this->canvas->fillRect(x, y, VIEW_BUTTON_W, VIEW_BUTTON_H,
                           COLOR_GREEN_FOREGND);
    this->canvas->setTextColor(COLOR_BLACK, COLOR_GREEN_FOREGND);
  } else {
    this->canvas->drawRect(x, y, VIEW_BUTTON_W, VIEW_BUTTON_H,
                           COLOR_GREEN_FOREGND);
    this->canvas->setTextColor(COLOR_GREEN_FOREGND, COLOR_BLACK);
  }

  int16_t throwAway;
  uint16_t w, h;

  this->canvas->getTextBounds(text, x, y, &throwAway, &throwAway, &w, &h);

  int16_t leftPad = ceil((VIEW_BUTTON_W - w) / 2);
  int16_t topPad = ceil((VIEW_BUTTON_H - h) / 2);

  this->canvas->setCursor(x + leftPad, y + topPad);
  this->canvas->print(text);
}

uint8_t BaseView::getCursorPosition(int8_t direction, uint8_t currentItem,
                                    uint8_t numItems) {

  if (direction >= 0) {
    uint8_t selectedIndex = currentItem + 1;

    if (selectedIndex >= numItems) {
      selectedIndex = 0;
    }

    return selectedIndex;
  }

  if (currentItem == 0) {
    return numItems - 1;
  }

  return currentItem - 1;
}

bool BaseView::updateCursor(uint8_t numItems) {
  bool didUpdate = false;

  if (this->state->interrupt == STATE_INTR_ROTARY &&
      this->state->rotary_direction != 0) {
    didUpdate = true;
    this->cursorIndex = BaseView::getCursorPosition(
        this->state->rotary_direction, this->cursorIndex, numItems);

  } else if (this->state->interrupt == STATE_INTR_MCP &&
             (this->state->mcp_up || this->state->mcp_down ||
              this->state->mcp_left || this->state->mcp_right)) {

    didUpdate = true;
    this->cursorIndex = BaseView::getCursorPosition(
        this->state->mcp_up || this->state->mcp_left ? -1 : 1,
        this->cursorIndex, numItems);
  }

  return didUpdate;
}

bool BaseView::didSelect() {
  return (this->state->interrupt == STATE_INTR_ROTARY_BTN &&
          this->state->rotary_btn) ||
         (this->state->interrupt == STATE_INTR_MCP && this->state->mcp_record);
}