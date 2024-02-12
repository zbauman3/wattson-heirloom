#include "./BaseView.h"

GFXcanvas16 globalCanvas(SCREEN_WIDTH, SCREEN_HEIGHT);

BaseView::BaseView(State *statePtr, Screen *screenPtr,
                   SetActiveViewPtr(setActiveViewPtr)) {
  this->state = statePtr;
  this->screen = screenPtr;
  this->canvas = &globalCanvas;
  this->isInitialRender = true;
  this->_setActiveView = setActiveViewPtr;
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
void BaseView::setup(){};