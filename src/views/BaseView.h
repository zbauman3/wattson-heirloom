#include "../controllers/Joystick.h"
#include "../feedback/Screen.h"
#include "../models/State.h"
#include <AceRoutine.h>
#include <Adafruit_GFX.h>
#include <Arduino.h>

#ifndef BaseView_H
#define BaseView_H

#define SetActiveViewPtr(name) void (*name)(uint8_t)

#define VIEW_PADDING 10
#define VIEW_TITLE_SPACE 60
#define VIEW_BUTTON_W (SCREEN_WIDTH - (VIEW_PADDING * 2))
#define VIEW_BUTTON_H 36

class BaseView : public ace_routine::Coroutine {
protected:
  State *state;
  Screen *screen;
  GFXcanvas16 *canvas;
  SetActiveViewPtr(_setActiveView);
  bool isInitialRender;

  uint8_t cursorIndex;

  void clearMainCanvas();
  void sendMainCanvas();
  void setActiveView(uint8_t view);
  void sendCanvas(GFXcanvas16 *newCanvas, int16_t x, int16_t y, int16_t w,
                  int16_t h);
  void drawTitle(String title, uint8_t hSize = 0);
  void drawButton(uint8_t position, uint8_t selectedMode, String text);

  bool updateCursor(uint8_t numItems);
  bool didSelect();

public:
  BaseView(State *statePtr, Screen *screenPtr,
           SetActiveViewPtr(setActiveViewPtr));

  void loop(bool isInitialRender);
  virtual void setup();
  virtual void cleanup();

  static uint8_t getCursorPosition(int8_t direction, uint8_t currentItem,
                                   uint8_t numItems);
};

#endif