#include "./DebugView.h"
using namespace ace_routine;

DebugView::DebugView(State *statePtr, Adafruit_ILI9341 *tftPtr,
                     Joystick *joystickPtr, SetActiveViewPtr(setActiveViewPtr))
    : BaseView(statePtr, tftPtr, setActiveViewPtr) {
  this->joystick = joystickPtr;
}

void DebugView::setup() {
  this->canvas->setTextColor(ILI9341_DARKGREEN, ILI9341_BLACK);
  this->canvas->setTextSize(2);
  this->canvas->setTextWrap(false);
}

int DebugView::runCoroutine() {
  COROUTINE_LOOP() {
    this->joystick->runCoroutine();

    if (this->state->hasInterrupt() && this->state->mcp_menu) {
      this->setActiveView(STATE_VIEW_RADAR);
      COROUTINE_YIELD();
    }

    if (this->isInitialRender || this->state->hasInterrupt() ||
        this->state->joystickChanged()) {

      this->canvas->setCursor(0, 0);

      this->canvas->printf("Joystick lr:      %d         \n",
                           this->state->joystick_lr);
      this->canvas->printf("joystick ud:      %d         \n",
                           this->state->joystick_ud);
      this->canvas->printf("rotary_pos:       %d         \n",
                           this->state->rotary_position);
      this->canvas->printf("rotary_isPressed: %d         \n",
                           this->state->rotary_btn);
      this->canvas->printf("btn_0_pressed:    %d         \n",
                           this->state->mcp_menu);
      this->canvas->printf("btn_1_pressed:    %d         \n",
                           this->state->mcp_up);
      this->canvas->printf("btn_2_pressed:    %d         \n",
                           this->state->mcp_record);

      this->canvas->printf("btn_3_pressed:    %d         \n",
                           this->state->mcp_left);
      this->canvas->printf("btn_4_pressed:    %d         \n",
                           this->state->mcp_down);
      this->canvas->printf("btn_5_pressed:    %d         \n",
                           this->state->mcp_right);
      this->canvas->printf("btn_6_pressed:    %d         \n",
                           this->state->mcp_one);
      this->canvas->printf("btn_7_pressed:    %d         \n",
                           this->state->mcp_two);
      this->canvas->printf("power_plug_gnd:   %d         \n",
                           this->state->mcp_power);
      this->canvas->printf("trigger_pressed:  %d         \n",
                           this->state->mcp_trigger);

      this->sendCanvas();
    }

    COROUTINE_YIELD();
  }
}