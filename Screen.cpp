#include "./Screen.h"
#include "./Macros.h"
#include "./PinDefs.h"
#include "./State.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <AceRoutine.h>
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>
using namespace ace_routine;

Screen::Screen(State *statePtr, Adafruit_MCP23X17 *mcpPtr,
               Joystick *joystickPtr)
    : tft(Adafruit_ILI9341(PinDefs::screenCS, PinDefs::screenDC)) {
  this->mcp = mcpPtr;
  this->joystick = joystickPtr;
  this->state = statePtr;
}

void Screen::begin() {
  this->mcp->pinMode(PinDefs::mcp_screenDimmer, OUTPUT);
  this->setBrightness(LOW);

  // give TFT time to boot
  delay(250);
  this->tft.begin();
  this->tft.setRotation(3);
  this->tft.fillScreen(ILI9341_BLACK);

  this->routineLoop = 0;

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

int Screen::runCoroutine() {
  COROUTINE_LOOP() {
    if (this->routine == 1) {
      this->joystick->sample();

      COROUTINE_YIELD();

      this->tft.setCursor(0, 0);
      this->tft.setTextColor(ILI9341_DARKGREEN, ILI9341_BLACK);
      this->tft.setTextSize(2);
      this->tft.setTextWrap(false);

      COROUTINE_YIELD();

      this->tft.printf("joystick lr:      %d         \n",
                       this->state->joystick_lr);
      this->tft.printf("joystick ud:      %d         \n",
                       this->state->joystick_ud);
      this->tft.printf("rotary_pos:       %d         \n",
                       this->state->rotary_position);
      this->tft.printf("rotary_isPressed: %d         \n",
                       this->state->rotary_btn);
      this->tft.printf("btn_0_pressed:    %d         \n",
                       this->state->mcp_menu);
      this->tft.printf("btn_1_pressed:    %d         \n", this->state->mcp_up);
      this->tft.printf("btn_2_pressed:    %d         \n",
                       this->state->mcp_record);

      COROUTINE_YIELD();

      this->tft.printf("btn_3_pressed:    %d         \n",
                       this->state->mcp_left);
      this->tft.printf("btn_4_pressed:    %d         \n",
                       this->state->mcp_down);
      this->tft.printf("btn_5_pressed:    %d         \n",
                       this->state->mcp_right);
      this->tft.printf("btn_6_pressed:    %d         \n", this->state->mcp_one);
      this->tft.printf("btn_7_pressed:    %d         \n", this->state->mcp_two);
      this->tft.printf("power_plug_gnd:   %d         \n",
                       this->state->mcp_power);
      this->tft.printf("trigger_pressed:  %d         \n",
                       this->state->mcp_trigger);
    }

    // if (this->routine == 0) {
    // `width()` is likely too expensive

    unsigned short last = this->routineLoop == 0 ? 15 : this->routineLoop - 1;

    this->tft.fillRect(this->tft.width() - 50, last * 10, 50, 10,
                       ILI9341_BLACK);

    this->tft.fillRect(this->tft.width() - 50, this->routineLoop * 10, 50, 10,
                       ILI9341_DARKGREEN);

    this->routineLoop++;
    if (this->routineLoop > 15) {
      this->routineLoop = 0;
    }

    COROUTINE_DELAY(750);
    // }

    this->routine = 0;
  }
}

void Screen::setBrightness(unsigned char brightness) {
  this->mcp->digitalWrite(PinDefs::mcp_screenDimmer, brightness);
  this->state->screenBrightness = brightness;
}

void Screen::toggleBrightness() {
  if (this->state->screenBrightness == LOW) {
    this->setBrightness(HIGH);
  } else {
    this->setBrightness(LOW);
  }
}

void Screen::tmp_display() {
  this->routine = 1;
  this->reset();
}