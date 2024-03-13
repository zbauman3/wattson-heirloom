#include "../models/State.h"
#include "./BaseView.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <AceRoutine.h>
#include <Arduino.h>

#ifndef SettingsView_H
#define SettingsView_H

class SettingsView : public BaseView {
private:
  bool shouldRender;
  uint8_t screen;
  void handleSelect();
  uint8_t getButtonCount();

  void drawMainMenu();
  void drawTheme();
  void drawReset();
  void drawPlugOverride();
  void drawTriggerOverride();

public:
  SettingsView(State *statePtr, Screen *screenPtr,
               SetActiveViewPtr(setActiveViewPtr));
  int runCoroutine() override;
  void setup() override;
};

#endif