#include "./ViewManager.h"

ViewManager *viewManagerPtr;
void setActiveViewCallback(uint8_t view) {
  viewManagerPtr->setActiveView(view);
}

ViewManager::ViewManager(State *statePtr, Screen *screenPtr,
                         Joystick *joystickPtr, Leds *ledsPtr,
                         LightRods *lightRodsPtr, Vibration *vibrationPtr,
                         Adafruit_EEPROM_I2C *eepromPtr)
    : debugView(statePtr, screenPtr, &setActiveViewCallback, joystickPtr),
      radarView(statePtr, screenPtr, &setActiveViewCallback, ledsPtr,
                lightRodsPtr),
      gamesView(statePtr, screenPtr, &setActiveViewCallback),
      lightsView(statePtr, screenPtr, &setActiveViewCallback, lightRodsPtr),
      settingsView(statePtr, screenPtr, &setActiveViewCallback, eepromPtr),
      menuView(statePtr, screenPtr, &setActiveViewCallback) {

  this->state = statePtr;
  this->screen = screenPtr;
  this->joystick = joystickPtr;
  this->leds = ledsPtr;
  this->lightRods = lightRodsPtr;
  this->vibration = vibrationPtr;
  this->eeprom = eepromPtr;

  this->debugTimer = 0;
  this->debugStep = 0;
  this->debugRotaryPos = 0;

  viewManagerPtr = this;
}

void ViewManager::loop() {
  this->checkMenuButton();
  this->checkDebugMode();

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
        this->leds->flashOnce(LEDS_GREEN, 150);
        this->debugStep = 2;
        this->debugTimer = millis();
      }
    }
  } else if (this->debugStep == 2 && this->state->rotary_btn) {
    if (millis() - this->debugTimer > 7000) {
      if (this->state->rotary_position == this->debugRotaryPos + 5) {
        this->leds->flashOnce(LEDS_GREEN, 150);
        this->setActiveView(STATE_VIEW_DEBUG);
      } else {
        this->leds->flashOnce(LEDS_RED, 150);
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

void ViewManager::checkMenuButton() {
  if (this->state->activeView != STATE_VIEW_MENU &&
      this->state->hasInterrupt() && this->state->mcp_menu) {
    this->setActiveView(STATE_VIEW_MENU);
  }
}