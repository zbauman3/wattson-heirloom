#include "./BaseView.h"

BaseView::BaseView(State *statePtr, Adafruit_ILI9341 *tftPtr) {
  this->state = statePtr;
  this->tft = tftPtr;
}