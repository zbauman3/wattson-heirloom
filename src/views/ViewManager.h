#include "../controllers/Joystick.h"
#include "../feedback/Leds.h"
#include "../feedback/LightRods.h"
#include "../feedback/Screen.h"
#include "../feedback/Vibration.h"
#include "../models/State.h"
#include "../views/DebugView.h"
#include "../views/GamesView.h"
#include "../views/LightsView.h"
#include "../views/MenuView.h"
#include "../views/RadarView.h"
#include "../views/SettingsView.h"
#include <Adafruit_EEPROM_I2C.h>
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
  Adafruit_EEPROM_I2C *eeprom;

  int debugTimer;
  uint8_t debugStep;
  int32_t debugRotaryPos;

  RadarView radarView;
  GamesView gamesView;
  LightsView lightsView;
  SettingsView settingsView;
  DebugView debugView;
  MenuView menuView;

  void checkDebugMode();

public:
  ViewManager(State *statePtr, Screen *screenPtr, Joystick *joystickPtr,
              Leds *ledsPtr, LightRods *lightRodsPtr, Vibration *vibrationPtr,
              Adafruit_EEPROM_I2C *eepromPtr);
  void loop();
  void setActiveView(uint8_t view);
};

#endif