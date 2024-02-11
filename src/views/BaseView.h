#include "../controllers/Joystick.h"
#include "../feedback/Screen.h"
#include "../models/State.h"
#include <AceRoutine.h>
#include <Adafruit_GFX.h>
#include <Arduino.h>

#ifndef BaseView_H
#define BaseView_H

#define SetActiveViewPtr(name) void (*name)(uint8_t)

class BaseView : public ace_routine::Coroutine {
protected:
  State *state;
  Screen *screen;
  GFXcanvas16 *canvas;
  SetActiveViewPtr(_setActiveView);
  bool isInitialRender;

  void sendCanvas();
  void setActiveView(uint8_t view);

public:
  BaseView(State *statePtr, Screen *screenPtr,
           SetActiveViewPtr(setActiveViewPtr));

  void loop(bool isInitialRender);
  virtual void setup();
};

#endif