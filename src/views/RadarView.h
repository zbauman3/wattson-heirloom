#include "../controllers/Joystick.h"
#include "../models/State.h"
#include "./BaseView.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <AceRoutine.h>
#include <Arduino.h>

#ifndef RadarView_H
#define RadarView_H

class RadarView : public BaseView {
private:
  Joystick *joystick;

public:
  RadarView(State *statePtr, Screen *screenPtr,
            SetActiveViewPtr(setActiveViewPtr), Joystick *joystickPtr);
  int runCoroutine() override;
  void setup() override;
};

#endif