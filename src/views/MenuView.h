#include "../models/State.h"
#include "../types.h"
#include "./BaseView.h"
#include <Arduino.h>

#ifndef MenuView_H
#define MenuView_H

#define MENU_ITEMS_COUNT 4
#define MENU_BUTTON_WIDTH 145
#define MENU_BUTTON_HEIGHT 66
#define MENU_BUTTON_PADDING 10

class MenuView : public BaseView {
private:
  uint8_t selectedIndex;
  void drawBox(int16_t x, int16_t y, String text, boolean active);

public:
  MenuView(State *statePtr, Screen *screenPtr,
           SetActiveViewPtr(setActiveViewPtr));
  int runCoroutine() override;
};

#endif