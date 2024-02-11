#include "./ViewManager.h"

ViewManager *viewManagerPtr;
void setActiveViewCallback(uint8_t view) {
  viewManagerPtr->setActiveView(view);
}

ViewManager::ViewManager(State *statePtr, Screen *screenPtr,
                         Joystick *joystickPtr, Leds *ledsPtr,
                         LightRods *lightRodsPtr, Vibration *vibrationPtr)
    : debugView(statePtr, screenPtr, &setActiveViewCallback, joystickPtr,
                ledsPtr),
      radarView(statePtr, screenPtr, &setActiveViewCallback, joystickPtr) {

  this->state = statePtr;
  this->screen = screenPtr;
  this->joystick = joystickPtr;
  this->leds = ledsPtr;
  this->lightRods = lightRodsPtr;
  this->vibration = vibrationPtr;

  viewManagerPtr = this;
}

void ViewManager::loop() {
  // Switching view happens inside the views `loop` fn.
  // This means that passing in `viewChanged` then
  // then setting it to `false` at the end of this fn
  // immediately overrides the `true` inside `setActiveView`
  bool didChangeView = this->state->viewChanged;
  this->state->viewChanged = false;

  switch (this->state->activeView) {
  case STATE_VIEW_RADAR:
    this->radarView.loop(didChangeView);
    break;

  default:
  case STATE_VIEW_DEBUG:
    this->debugView.loop(didChangeView);
    break;
  }

  this->debugView.enterDebug();
}

void ViewManager::setActiveView(uint8_t view) {
  this->state->activeView = view;
  this->state->viewChanged = true;
}