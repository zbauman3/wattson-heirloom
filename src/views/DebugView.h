#include "../controllers/Joystick.h"
#include "../feedback/Leds.h"
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
  Leds *leds;

  int debugTimer;
  uint8_t debugStep;
  signed long debugRotaryPos;

public:
  DebugView(State *statePtr, Screen *screenPtr,
            SetActiveViewPtr(setActiveViewPtr), Joystick *joystickPtr,
            Leds *ledsPtr);
  int runCoroutine() override;
  void setup() override;
  void enterDebug();
};

#endif