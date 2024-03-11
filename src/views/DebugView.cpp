#include "./DebugView.h"
using namespace ace_routine;

DebugView::DebugView(State *statePtr, Screen *screenPtr,
                     SetActiveViewPtr(setActiveViewPtr), Joystick *joystickPtr)
    : BaseView(statePtr, screenPtr, setActiveViewPtr) {
  this->joystick = joystickPtr;
}

void DebugView::setup() {
  this->canvas->setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  this->canvas->setTextSize(1);
  this->canvas->setTextWrap(false);

  this->lastInterrupt = STATE_INTR_EMPTY;
  this->holdTimer = 0;
}

int DebugView::runCoroutine() {
  COROUTINE_LOOP() {
    if (this->state->interrupt == STATE_INTR_MCP && this->state->mcp_menu &&
        this->holdTimer == 0) {
      this->holdTimer = millis();
    } else if (this->holdTimer != 0) {
      if (this->state->mcp_menu) {
        if (millis() - this->holdTimer > 5000) {
          this->setActiveView(STATE_VIEW_SETTINGS);
          this->holdTimer = 0;
          COROUTINE_YIELD();
        }
      } else {
        this->holdTimer = 0;
      }
    }

    this->joystick->runCoroutine();

    if (this->isInitialRender ||
        this->state->interrupt != this->lastInterrupt ||
        this->state->joystickChanged()) {
      this->lastInterrupt = this->state->interrupt;

      this->canvas->setCursor(0, 0);

      this->canvas->println("-------- DEBUG --------");

      this->canvas->printf("Interrupt:        %d    \n",
                           this->state->interrupt);
      this->canvas->printf("Joystick lr:      %d    \n",
                           this->state->joystick_lr);
      this->canvas->printf("joystick ud:      %d    \n",
                           this->state->joystick_ud);
      this->canvas->printf("rotary_pos:       %d    \n",
                           this->state->rotary_position);
      this->canvas->printf("rotary_isPressed: %d    \n",
                           this->state->rotary_btn);
      this->canvas->printf("mcp_menu:         %d    \n", this->state->mcp_menu);
      this->canvas->printf("mcp_up:           %d    \n", this->state->mcp_up);
      this->canvas->printf("mcp_record:       %d    \n",
                           this->state->mcp_record);

      this->canvas->printf("mcp_left:         %d    \n", this->state->mcp_left);
      this->canvas->printf("mcp_down:         %d    \n", this->state->mcp_down);
      this->canvas->printf("mcp_right:        %d    \n",
                           this->state->mcp_right);
      this->canvas->printf("mcp_one:          %d    \n", this->state->mcp_one);
      this->canvas->printf("mcp_two:          %d    \n", this->state->mcp_two);
      this->canvas->printf("power_plug_gnd:   %d    \n",
                           this->state->mcp_power);
      this->canvas->printf("trigger_pressed:  %d    \n",
                           this->state->mcp_trigger);

      this->sendMainCanvas();
    }

    COROUTINE_YIELD();
  }
}