#include "../controllers/Joystick.h"
#include "../models/State.h"
#include "../types.h"
#include "./BaseView.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <AceRoutine.h>
#include <Arduino.h>

#ifndef RadarView_H
#define RadarView_H

class RadarView : public BaseView {
private:
  Coord pingCurrent;
  Coord pingEnd;

  void drawRadarBackground();
  void drawRadarPing(int16_t x0, int16_t y0);
  void moveRadarPing();

public:
  RadarView(State *statePtr, Screen *screenPtr,
            SetActiveViewPtr(setActiveViewPtr));
  int runCoroutine() override;
  void setup() override;
};

#endif