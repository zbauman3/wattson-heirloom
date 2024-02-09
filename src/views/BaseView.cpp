#include "./BaseView.h"

BaseView::BaseView(State *statePtr, Adafruit_ILI9341 *tftPtr)
    : canvas(320, 240) {
  this->state = statePtr;
  this->tft = tftPtr;
}

void BaseView::sendCanvas() {
  this->tft->drawRGBBitmap(0, 0, this->canvas.getBuffer(), this->canvas.width(),
                           this->canvas.height());
}