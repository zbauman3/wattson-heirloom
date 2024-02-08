#include "./DebugView.h"
using namespace ace_routine;

DebugView::DebugView(State *statePtr, Adafruit_ILI9341 *tftPtr,
                     Joystick *joystickPtr)
    : BaseView(statePtr, tftPtr) {
  this->joystick = joystickPtr;
}

int DebugView::runCoroutine() {
  COROUTINE_LOOP() {
    this->joystick->sample();

    COROUTINE_YIELD();

    this->tft->setCursor(0, 0);
    this->tft->setTextColor(ILI9341_DARKGREEN, ILI9341_BLACK);
    this->tft->setTextSize(2);
    this->tft->setTextWrap(false);

    COROUTINE_YIELD();

    this->tft->printf("Joystick lr:      %d         \n",
                      this->state->joystick_lr);
    this->tft->printf("joystick ud:      %d         \n",
                      this->state->joystick_ud);
    this->tft->printf("rotary_pos:       %d         \n",
                      this->state->rotary_position);
    this->tft->printf("rotary_isPressed: %d         \n",
                      this->state->rotary_btn);
    this->tft->printf("btn_0_pressed:    %d         \n", this->state->mcp_menu);
    this->tft->printf("btn_1_pressed:    %d         \n", this->state->mcp_up);
    this->tft->printf("btn_2_pressed:    %d         \n",
                      this->state->mcp_record);

    COROUTINE_YIELD();

    this->tft->printf("btn_3_pressed:    %d         \n", this->state->mcp_left);
    this->tft->printf("btn_4_pressed:    %d         \n", this->state->mcp_down);
    this->tft->printf("btn_5_pressed:    %d         \n",
                      this->state->mcp_right);
    this->tft->printf("btn_6_pressed:    %d         \n", this->state->mcp_one);
    this->tft->printf("btn_7_pressed:    %d         \n", this->state->mcp_two);
    this->tft->printf("power_plug_gnd:   %d         \n",
                      this->state->mcp_power);
    this->tft->printf("trigger_pressed:  %d         \n",
                      this->state->mcp_trigger);

    COROUTINE_DELAY(750);
  }
}