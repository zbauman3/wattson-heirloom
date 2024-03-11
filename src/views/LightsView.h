#include "../feedback/LightRods.h"
#include "../models/State.h"
#include "./BaseView.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <AceRoutine.h>
#include <Arduino.h>

#ifndef LightsView_H
#define LightsView_H

class LightsView : public BaseView {
private:
  LightRods *lightRods;

  bool shouldRender;

  uint8_t screen;
  uint8_t mode;
  uint8_t brightness;
  uint8_t speed;
  bool direction;
  uint8_t color;

  void handleSelect();
  uint8_t getButtonCount();

  void drawMainMenu();
  void drawModeMenu();
  void drawBrightnessMenu();
  void drawSpeedMenu();
  void drawDirectionMenu();
  void drawColorMenu();

public:
  LightsView(State *statePtr, Screen *screenPtr,
             SetActiveViewPtr(setActiveViewPtr), LightRods *lightRodsPtr);
  int runCoroutine() override;
  void setup() override;
  void cleanup() override;
};

#endif