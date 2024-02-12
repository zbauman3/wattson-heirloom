#include "./ViewManager.h"

ViewManager *viewManagerPtr;
void setActiveViewCallback(uint8_t view) {
  viewManagerPtr->setActiveView(view);
}

ViewManager::ViewManager(State *statePtr, Screen *screenPtr,
                         Joystick *joystickPtr, Leds *ledsPtr,
                         LightRods *lightRodsPtr, Vibration *vibrationPtr)
    : debugView(statePtr, screenPtr, &setActiveViewCallback, joystickPtr),
      radarView(statePtr, screenPtr, &setActiveViewCallback) {

  this->state = statePtr;
  this->screen = screenPtr;
  this->joystick = joystickPtr;
  this->leds = ledsPtr;
  this->lightRods = lightRodsPtr;
  this->vibration = vibrationPtr;

  this->debugTimer = 0;
  this->debugStep = 0;
  this->debugRotaryPos = 0;

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

  this->checkDebugMode();
}

void ViewManager::setActiveView(uint8_t view) {
  this->state->activeView = view;
  this->state->viewChanged = true;
}

void ViewManager::checkDebugMode() {
  // Enter debug:
  // 1. click & hold rotary, without moving, for 7 seconds
  // 2. continue holding, twist left 5 clicks, hold for 7 seconds
  //
  // Exit debug:
  // 1. click & hold rotary, without moving, for 7 seconds
  if (this->state->hasInterrupt() && this->debugStep == 0 &&
      this->state->rotary_btn) {
    this->debugStep = 1;
    this->debugTimer = millis();
    this->debugRotaryPos = this->state->rotary_position;
  } else if (this->debugStep == 1 && this->state->rotary_btn &&
             this->state->rotary_position == this->debugRotaryPos) {
    if (millis() - this->debugTimer > 7000) {
      if (this->state->activeView == STATE_VIEW_DEBUG) {
        this->setActiveView(STATE_VIEW_INIT);
      } else {
        this->leds->flashGreen();
        this->debugStep = 2;
        this->debugTimer = millis();
      }
    }
  } else if (this->debugStep == 2 && this->state->rotary_btn) {
    if (millis() - this->debugTimer > 7000) {
      if (this->state->rotary_position == this->debugRotaryPos + 5) {
        this->leds->flashGreen();
        this->setActiveView(STATE_VIEW_DEBUG);
      } else {
        this->leds->flashRed();
      }

      this->debugStep = 0;
      this->debugTimer = 0;
      this->debugRotaryPos = 0;
    }
  } else if (this->debugStep != 0) {
    this->debugStep = 0;
    this->debugTimer = 0;
    this->debugRotaryPos = 0;
  }
}
