#include "../models/State.h"
#include "./BaseView.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <AceRoutine.h>
#include <Adafruit_EEPROM_I2C.h>
#include <Arduino.h>

#ifndef SettingsView_H
#define SettingsView_H

class SettingsView : public BaseView {
private:
  Adafruit_EEPROM_I2C *eeprom;

  uint8_t lastEeprom;

  bool shouldRender;
  uint8_t screen;
  void handleSelect();
  uint8_t getButtonCount();

  void drawMainMenu();

public:
  SettingsView(State *statePtr, Screen *screenPtr,
               SetActiveViewPtr(setActiveViewPtr),
               Adafruit_EEPROM_I2C *eepromPtr);
  int runCoroutine() override;
  void setup() override;
};

#endif