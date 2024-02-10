#include "./RadarView.h"
using namespace ace_routine;

RadarView::RadarView(State *statePtr, Adafruit_ILI9341 *tftPtr,
                     Joystick *joystickPtr)
    : BaseView(statePtr, tftPtr) {
  this->joystick = joystickPtr;
}

int RadarView::runCoroutine() {
  COROUTINE_LOOP() { COROUTINE_YIELD(); }
}