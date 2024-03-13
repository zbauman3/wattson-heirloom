#include "../models/State.h"
#include "../types.h"
#include "./BaseView.h"
#include <Arduino.h>

#ifndef MenuView_H
#define MenuView_H

#define MENU_VIEW_ITEMS 3

class MenuView : public BaseView {

public:
  MenuView(State *statePtr, Screen *screenPtr,
           SetActiveViewPtr(setActiveViewPtr));
  int runCoroutine() override;
};

#endif