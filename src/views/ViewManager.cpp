#include "./ViewManager.h"

ViewManager *viewManagerPtr;
void setActiveViewCallback(uint8_t view) {
  viewManagerPtr->setActiveView(view);
}

ViewManager::ViewManager(State *statePtr, Screen *screenPtr,
                         Joystick *joystickPtr, Leds *ledsPtr,
                         LightRods *lightRodsPtr, Vibration *vibrationPtr)
    : debugView(statePtr, screenPtr, &setActiveViewCallback, joystickPtr),
      radarView(statePtr, screenPtr, &setActiveViewCallback, ledsPtr,
                lightRodsPtr),
      gamesView(statePtr, screenPtr, &setActiveViewCallback),
      lightsView(statePtr, screenPtr, &setActiveViewCallback, lightRodsPtr),
      settingsView(statePtr, screenPtr, &setActiveViewCallback),
      menuView(statePtr, screenPtr, &setActiveViewCallback) {

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
  this->checkMenuButton();

  // Switching view happens inside the views `loop` fn. So updating
  // `viewChanged` at the _end_ of this `loop clobbers the update
  bool isInitialRender = this->state->viewChanged;
  this->state->viewChanged = false;

  switch (this->state->activeView) {
  case STATE_VIEW_MENU:
    this->menuView.loop(isInitialRender);
    break;

  case STATE_VIEW_RADAR:
    this->radarView.loop(isInitialRender);
    break;

  case STATE_VIEW_GAMES:
    this->gamesView.loop(isInitialRender);
    break;

  case STATE_VIEW_LIGHTS:
    this->lightsView.loop(isInitialRender);
    break;

  case STATE_VIEW_SETTINGS:
    this->settingsView.loop(isInitialRender);
    break;

  default:
  case STATE_VIEW_DEBUG:
    this->debugView.loop(isInitialRender);
    break;
  }
}

void ViewManager::setActiveView(uint8_t view) {
  switch (this->state->activeView) {
  case STATE_VIEW_MENU:
    this->menuView.cleanup();
    break;

  case STATE_VIEW_RADAR:
    this->radarView.cleanup();
    break;

  case STATE_VIEW_GAMES:
    this->gamesView.cleanup();
    break;

  case STATE_VIEW_LIGHTS:
    this->lightsView.cleanup();
    break;

  case STATE_VIEW_SETTINGS:
    this->settingsView.cleanup();
    break;

  default:
  case STATE_VIEW_DEBUG:
    this->debugView.cleanup();
    break;
  }

  this->state->activeView = view;
  this->state->viewChanged = true;
}

void ViewManager::checkMenuButton() {
  if (this->state->activeView != STATE_VIEW_MENU &&
      this->state->activeView != STATE_VIEW_DEBUG &&
      this->state->interrupt == STATE_INTR_MCP && this->state->mcp_menu) {
    this->setActiveView(STATE_VIEW_MENU);
  }
}