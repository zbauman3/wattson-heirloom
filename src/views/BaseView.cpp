#include "./BaseView.h"

GFXcanvas16 globalCanvas(320, 240);

BaseView::BaseView(State *statePtr, Adafruit_ILI9341 *tftPtr,
                   SetActiveViewPtr(setActiveViewPtr)) {
  this->state = statePtr;
  this->tft = tftPtr;
  this->canvas = &globalCanvas;
  this->isInitialRender = true;
  this->_setActiveView = setActiveViewPtr;
}

void BaseView::sendCanvas() {
  this->tft->drawRGBBitmap(0, 0, this->canvas->getBuffer(),
                           this->canvas->width(), this->canvas->height());
}

void BaseView::setActiveView(uint8_t view) { this->_setActiveView(view); }

void BaseView::loop(bool _isInitialRender) {
  this->isInitialRender = _isInitialRender;

  if (_isInitialRender) {
    this->reset();
    this->canvas->fillScreen(ILI9341_BLACK);
    this->setup();
  }

  this->runCoroutine();

  if (_isInitialRender) {
    this->isInitialRender = false;
  }
}

// this should be overriden
void BaseView::setup(){};