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

  void clearMainCanvas();
  void sendMainCanvas();
  void setActiveView(uint8_t view);
  boolean changeToMenu();
  void sendCanvas(GFXcanvas16 *newCanvas, int16_t x, int16_t y, int16_t w,
                  int16_t h);

public:
  BaseView(State *statePtr, Screen *screenPtr,
           SetActiveViewPtr(setActiveViewPtr));

  void loop(bool isInitialRender);
  virtual void setup();
};

#endif