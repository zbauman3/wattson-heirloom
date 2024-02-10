#include "../controllers/Joystick.h"
// #include "../feedback/Screen.h"
#include "../models/State.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <AceRoutine.h>
#include <Arduino.h>

#ifndef BaseView_H
#define BaseView_H

#define VIEW_DEBUG 0x00
#define VIEW_RADAR 0x01

#define SetActiveViewPtr(name) void (*name)(uint8_t)

class BaseView : public ace_routine::Coroutine {
protected:
  State *state;
  Adafruit_ILI9341 *tft;
  GFXcanvas16 *canvas;
  SetActiveViewPtr(_setActiveView);
  bool isInitialRender;

  void sendCanvas();
  void setActiveView(uint8_t view);

public:
  BaseView(State *statePtr, Adafruit_ILI9341 *tftPtr,
           SetActiveViewPtr(setActiveViewPtr));

  void loop(bool isInitialRender);
  virtual void setup();
};

#endif