#include "./DebugView.h"
using namespace ace_routine;

DebugView::DebugView(State *statePtr, Adafruit_ILI9341 *tftPtr,
                     Joystick *joystickPtr)
    : BaseView(statePtr, tftPtr) {
  this->joystick = joystickPtr;
  this->lastJoystickLr = 0;
  this->lastJoystickUd = 0;
}

int DebugView::runCoroutine() {
  COROUTINE_LOOP() {
    this->joystick->sample();

    uint8_t joystickUdDiff =
        abs(this->state->joystick_ud - this->lastJoystickUd);
    uint8_t lastJoystickLr =
        abs(this->state->joystick_lr - this->lastJoystickLr);

    if (this->state->hasInterrupt() || joystickUdDiff > 2 ||
        lastJoystickLr > 2) {

      this->lastJoystickLr = this->state->joystick_lr;
      this->lastJoystickUd = this->state->joystick_ud;

      COROUTINE_YIELD();

      this->canvas.setCursor(0, 0);
      this->canvas.setTextColor(ILI9341_DARKGREEN, ILI9341_BLACK);
      this->canvas.setTextSize(2);
      this->canvas.setTextWrap(false);

      COROUTINE_YIELD();

      this->canvas.printf("Joystick lr:      %d         \n",
                          this->state->joystick_lr);
      this->canvas.printf("joystick ud:      %d         \n",
                          this->state->joystick_ud);
      this->canvas.printf("rotary_pos:       %d         \n",
                          this->state->rotary_position);
      this->canvas.printf("rotary_isPressed: %d         \n",
                          this->state->rotary_btn);
      this->canvas.printf("btn_0_pressed:    %d         \n",
                          this->state->mcp_menu);
      this->canvas.printf("btn_1_pressed:    %d         \n",
                          this->state->mcp_up);
      this->canvas.printf("btn_2_pressed:    %d         \n",
                          this->state->mcp_record);

      COROUTINE_YIELD();

      this->canvas.printf("btn_3_pressed:    %d         \n",
                          this->state->mcp_left);
      this->canvas.printf("btn_4_pressed:    %d         \n",
                          this->state->mcp_down);
      this->canvas.printf("btn_5_pressed:    %d         \n",
                          this->state->mcp_right);
      this->canvas.printf("btn_6_pressed:    %d         \n",
                          this->state->mcp_one);
      this->canvas.printf("btn_7_pressed:    %d         \n",
                          this->state->mcp_two);
      this->canvas.printf("power_plug_gnd:   %d         \n",
                          this->state->mcp_power);
      this->canvas.printf("trigger_pressed:  %d         \n",
                          this->state->mcp_trigger);

      COROUTINE_YIELD();

      this->sendCanvas();
    } else {
      COROUTINE_YIELD();
    }
  }
}