#include "../models/State.h"
#include "./BaseView.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <AceRoutine.h>
#include <Arduino.h>

#ifndef LightsView_H
#define LightsView_H

class LightsView : public BaseView {
public:
  LightsView(State *statePtr, Screen *screenPtr,
             SetActiveViewPtr(setActiveViewPtr));
  int runCoroutine() override;
};

#endif