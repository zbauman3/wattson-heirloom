#include "../models/State.h"
#include "./BaseView.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <AceRoutine.h>
#include <Arduino.h>

#ifndef GamesView_H
#define GamesView_H

class GamesView : public BaseView {
public:
  GamesView(State *statePtr, Screen *screenPtr,
            SetActiveViewPtr(setActiveViewPtr));
  int runCoroutine() override;
};

#endif