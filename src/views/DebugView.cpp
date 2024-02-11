#include "./DebugView.h"
using namespace ace_routine;

DebugView::DebugView(State *statePtr, Screen *screenPtr,
                     SetActiveViewPtr(setActiveViewPtr), Joystick *joystickPtr,
                     Leds *ledsPtr)
    : BaseView(statePtr, screenPtr, setActiveViewPtr) {
  this->joystick = joystickPtr;
  this->leds = ledsPtr;
  this->debugTimer = 0;
  this->debugStep = 0;
  this->debugRotaryPos = 0;
}

void DebugView::setup() {
  this->canvas->setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  this->canvas->setTextSize(1);
  this->canvas->setTextWrap(false);
}

void DebugView::enterDebug() {
  if (this->debugStep == 5) {
    this->debugTimer = 0;
    this->debugStep = 0;
    this->debugRotaryPos = 0;
    if (this->state->activeView == STATE_VIEW_DEBUG) {
      this->setActiveView(STATE_VIEW_INIT);
    } else {
      this->setActiveView(STATE_VIEW_DEBUG);
    }
  }

  if (this->state->hasInterrupt()) {
    if (this->state->rotary_btn) {
      if (this->debugStep == 0) {
        this->debugTimer = millis();
        this->debugRotaryPos = this->state->rotary_position;
        this->debugStep = 1;
      } else if (this->debugStep == 1 &&
                 this->state->rotary_position == this->debugRotaryPos + 5) {
        if (this->state->activeView == STATE_VIEW_DEBUG) {
          this->leds->flashGreen();
          this->debugStep = 5;
        } else {
          this->debugTimer = millis();
          this->debugRotaryPos = this->state->rotary_position;
          this->debugStep = 2;
        }
      } else if (this->debugStep == 2 &&
                 this->state->rotary_position == this->debugRotaryPos - 5) {
        this->debugTimer = millis();
        this->leds->flashGreen();
        this->debugRotaryPos = this->state->rotary_position;
        this->debugStep = 3;
      } else if (this->debugStep == 3 &&
                 this->state->rotary_position == this->debugRotaryPos - 5) {
        this->debugTimer = millis();
        this->leds->flashGreen();
        this->debugRotaryPos = this->state->rotary_position;
        this->debugStep = 4;
      } else if (this->debugStep == 4 &&
                 this->state->rotary_position == this->debugRotaryPos + 5) {
        this->leds->flashGreen();
        this->debugStep = 5;
      } else if (this->debugStep > 0 && millis() - this->debugTimer > 3000) {
        if (this->debugStep > 1) {
          this->leds->flashGreen();
          this->leds->flashRed();
        }
        this->debugTimer = 0;
        this->debugRotaryPos = 0;
        this->debugStep = 0;
      }
    } else if (this->debugStep > 0) {
      if (this->debugStep > 1) {
        this->leds->flashGreen();
        this->leds->flashRed();
      }
      this->debugTimer = 0;
      this->debugRotaryPos = 0;
      this->debugStep = 0;
    }
  }
}

int DebugView::runCoroutine() {
  COROUTINE_LOOP() {
    this->joystick->runCoroutine();

    if (this->isInitialRender || this->state->hasInterrupt() ||
        this->state->joystickChanged()) {

      this->canvas->setCursor(0, 0);

      this->canvas->println("-------- DEBUG --------");

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

      this->sendCanvas();
    }

    COROUTINE_YIELD();
  }
}