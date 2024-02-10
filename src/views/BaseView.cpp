#include "./BaseView.h"

GFXcanvas16 globalCanvas(320, 240);

BaseView::BaseView(State *statePtr, Adafruit_ILI9341 *tftPtr) {
  this->state = statePtr;
  this->tft = tftPtr;
  this->canvas = &globalCanvas;
  this->rendered = false;
}

void BaseView::sendCanvas() {
  this->tft->drawRGBBitmap(0, 0, this->canvas->getBuffer(),
                           this->canvas->width(), this->canvas->height());
}