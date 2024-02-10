#include "../controllers/Joystick.h"
#include "../models/State.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <AceRoutine.h>
#include <Arduino.h>

#ifndef BaseView_H
#define BaseView_H

class BaseView : public ace_routine::Coroutine {
protected:
  State *state;
  Adafruit_ILI9341 *tft;
  GFXcanvas16 *canvas;
  bool rendered;

  void sendCanvas();

public:
  BaseView(State *statePtr, Adafruit_ILI9341 *tftPtr);
};

#endif