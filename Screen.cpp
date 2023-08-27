#include "./Screen.h"
#include "./Macros.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Arduino.h>

Screen::Screen(signed char cs, signed char dc)
    : tft(Adafruit_ILI9341(cs, dc)) {}

void Screen::begin() {
  // give TFT time to boot
  delay(500);
  this->tft.begin();
  this->tft.setRotation(3);
  this->tft.fillScreen(ILI9341_BLACK);

  DEBUG_BLOCK({
    // read diagnostics
    uint8_t x = this->tft.readcommand8(ILI9341_RDMODE);
    DEBUG("Display Power Mode: 0x");
    DEBUG_LN(x, HEX);
    x = this->tft.readcommand8(ILI9341_RDMADCTL);
    DEBUG("MADCTL Mode: 0x");
    DEBUG_LN(x, HEX);
    x = this->tft.readcommand8(ILI9341_RDPIXFMT);
    DEBUG("Pixel Format: 0x");
    DEBUG_LN(x, HEX);
    x = this->tft.readcommand8(ILI9341_RDIMGFMT);
    DEBUG("Image Format: 0x");
    DEBUG_LN(x, HEX);
    x = this->tft.readcommand8(ILI9341_RDSELFDIAG);
    DEBUG("Self Diagnostic: 0x");
    DEBUG_LN(x, HEX);
  });
}

void Screen::tmp_display(unsigned char joystickLr, unsigned char joystickUd,
                         signed long rotary_pos, bool btn_0_pressed,
                         bool btn_1_pressed, bool btn_2_pressed,
                         bool btn_3_pressed, bool btn_4_pressed,
                         bool btn_5_pressed, bool btn_6_pressed,
                         bool btn_7_pressed, bool power_plug_grounded,
                         bool trigger_pressed) {
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.setTextSize(2);
  tft.setTextWrap(false);

  tft.printf("joystick lr:     %d         \n", joystickLr);
  tft.printf("joystick ud:     %d         \n", joystickUd);
  tft.printf("rotary_pos:      %d         \n", rotary_pos);
  tft.printf("btn_0_pressed:   %d         \n", btn_0_pressed);
  tft.printf("btn_1_pressed:   %d         \n", btn_1_pressed);
  tft.printf("btn_2_pressed:   %d         \n", btn_2_pressed);
  tft.printf("btn_3_pressed:   %d         \n", btn_3_pressed);
  tft.printf("btn_4_pressed:   %d         \n", btn_4_pressed);
  tft.printf("btn_5_pressed:   %d         \n", btn_5_pressed);
  tft.printf("btn_6_pressed:   %d         \n", btn_6_pressed);
  tft.printf("btn_7_pressed:   %d         \n", btn_7_pressed);
  tft.printf("power_plug_gnd:  %d         \n", power_plug_grounded);
  tft.printf("trigger_pressed: %d         \n", trigger_pressed);
}