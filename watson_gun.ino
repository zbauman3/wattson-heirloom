#include "./FeedbackLEDs.h"
#include "./Interrupts.h"
#include "./Joystick.h"
#include "./LightRods.h"
#include "./Macros.h"
#include "./Rotary.h"
#include "./Screen.h"
#include "./State.h"
#include "./Vibration.h"
#include <Adafruit_MCP23X17.h>

Adafruit_MCP23X17 mcp;
LightRods lightRods = LightRods();
Joystick joystick;
FeedbackLEDs feedbackLEDs = FeedbackLEDs(&mcp);
Rotary rotary = Rotary();
Screen screen = Screen(&mcp);
Vibration vibe = Vibration(&mcp);
State state = State();
Interrupts interrupts = Interrupts(&state, &mcp, &rotary);

void setup() {
  DEBUG_INIT(9600);
  DEBUG_LN("Started!");
  analogReadResolution(8);

  if (!mcp.begin_I2C()) {
    DEBUG_LN("Error beginning MCP23017.");
    INFINITE_LOOP;
  }

  if (!rotary.begin()) {
    INFINITE_LOOP;
  }

  lightRods.begin();
  screen.begin();
  joystick.begin();
  feedbackLEDs.begin();
  vibe.begin();
  interrupts.begin();
}

// TODO move this to the screen
bool firstDraw = true;

void loop(void) {

  interrupts.loop();

  if (!firstDraw && !state.hasInterrupt()) {
    return;
  }

  DEBUG_LN("--Acting--");

  firstDraw = false;

  // joystickValues joystickPos = joystick.sample();
  // signed long rotary_pos = rotary.getValue();
  // signed long rotary_isPressed = rotary.isPressed();
  // bool btn_0_pressed = miscIO.isPressed(miscIO.menu);
  // bool btn_1_pressed = miscIO.isPressed(miscIO.up);
  // bool btn_2_pressed = miscIO.isPressed(miscIO.record);
  // bool btn_3_pressed = miscIO.isPressed(miscIO.left);
  // bool btn_4_pressed = miscIO.isPressed(miscIO.down);
  // bool btn_5_pressed = miscIO.isPressed(miscIO.right);
  // bool btn_6_pressed = miscIO.isPressed(miscIO.one);
  // bool btn_7_pressed = miscIO.isPressed(miscIO.two);
  // bool trigger_pressed = miscIO.isPressed(miscIO.trigger);
  // bool power_plug_grounded = miscIO.isPressed(miscIO.power);

  // screen.tmp_display(joystickPos.lr, joystickPos.ud, rotary_pos,
  //                    rotary_isPressed, btn_0_pressed, btn_1_pressed,
  //                    btn_2_pressed, btn_3_pressed, btn_4_pressed,
  //                    btn_5_pressed, btn_6_pressed, btn_7_pressed,
  //                    power_plug_grounded, trigger_pressed);

  // if (btn_0_pressed) {
  //   if (power_plug_grounded) {
  //     lightRods.tmp_fill(255, 0, 255);
  //   } else {
  //     lightRods.tmp_fill(122, 0, 122);
  //   }
  //   delay(150);
  //   lightRods.off();
  // }

  // if (btn_1_pressed) {
  //   feedbackLEDs.on(FEEDBACK_GREEN);
  //   delay(150);
  //   feedbackLEDs.off(FEEDBACK_GREEN);
  // }

  // if (btn_2_pressed) {
  //   feedbackLEDs.on(FEEDBACK_RED);
  //   delay(150);
  //   feedbackLEDs.off(FEEDBACK_RED);
  // }

  // if (btn_3_pressed) {
  //   screen.toggleBrightness();
  // }

  // if (btn_4_pressed) {
  //   vibe.tmp_vibrate();
  // }
}