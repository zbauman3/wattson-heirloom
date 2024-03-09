#include "../controllers/Joystick.h"
#include "../models/State.h"
#include "./BaseView.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <AceRoutine.h>
#include <Arduino.h>

#ifndef DebugView_H
#define DebugView_H

class DebugView : public BaseView {
private:
  Joystick *joystick;

public:
  DebugView(State *statePtr, Screen *screenPtr,
            SetActiveViewPtr(setActiveViewPtr), Joystick *joystickPtr);
  int runCoroutine() override;
  void setup() override;
};

#endif