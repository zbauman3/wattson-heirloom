#include "../controllers/Joystick.h"
#include "../feedback/Leds.h"
#include "../feedback/LightRods.h"
#include "../feedback/Screen.h"
#include "../feedback/Vibration.h"
#include "../models/State.h"
#include "../views/DebugView.h"
#include "../views/RadarView.h"
#include <Arduino.h>

#ifndef ViewManager_H
#define ViewManager_H

class ViewManager {
private:
  State *state;
  Screen *screen;
  Joystick *joystick;
  Leds *leds;
  LightRods *lightRods;
  Vibration *vibration;

  RadarView radarView;
  DebugView debugView;

public:
  ViewManager(State *statePtr, Screen *screenPtr, Joystick *joystickPtr,
              Leds *ledsPtr, LightRods *lightRodsPtr, Vibration *vibrationPtr);
  void loop();
  void setActiveView(uint8_t view);
};

#endif