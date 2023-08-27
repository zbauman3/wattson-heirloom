#include "./Macros.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#ifndef Screen_H
#define Screen_H

#define SCREEN_BRIGHTNESS_LOW 0x00
#define SCREEN_BRIGHTNESS_HIGH 0x01

class Screen {
private:
  Adafruit_ILI9341 tft;
  Adafruit_MCP23X17 *mcp;
  unsigned char dimmer;

public:
  Screen(signed char cs, signed char dc, Adafruit_MCP23X17 *mcpPtr,
         unsigned char dimmerPin);
  void begin();
  void setBrightness(unsigned char brightness);
  void toggleBrightness();
  void tmp_display(unsigned char joystickLr, unsigned char joystickUd,
                   signed long rotary_pos, bool btn_0_pressed,
                   bool btn_1_pressed, bool btn_2_pressed, bool btn_3_pressed,
                   bool btn_4_pressed, bool btn_5_pressed, bool btn_6_pressed,
                   bool btn_7_pressed, bool power_plug_grounded,
                   bool trigger_pressed);
};

#endif