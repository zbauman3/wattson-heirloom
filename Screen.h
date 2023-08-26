#include "./Macros.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Arduino.h>

#ifndef Z_Screen_H
#define Z_Screen_H

class Z_Screen {
private:
  Adafruit_ILI9341 tft;

public:
  Z_Screen(signed char cs, signed char dc);
  void begin();
  void tmp_display(unsigned char joystickLr, unsigned char joystickUd,
                   signed long rotary_pos, bool btn_0_pressed,
                   bool btn_1_pressed, bool btn_2_pressed, bool btn_3_pressed,
                   bool btn_4_pressed, bool btn_5_pressed, bool btn_6_pressed,
                   bool btn_7_pressed, bool power_plug_grounded);
};

#endif