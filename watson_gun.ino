#include "./FeedbackLEDs.h"
#include "./Interrupts.h"
#include "./Joystick.h"
#include "./LightRods.h"
#include "./Macros.h"
#include "./MiscIO.h"
#include "./Rotary.h"
#include "./Screen.h"
#include "./State.h"
#include "./Vibration.h"
#include <Adafruit_MCP23X17.h>

#define TFT_DC 20
#define TFT_CS 21
#define INTERRUPT_PIN 4
#define NEOPIXEL_PIN 3
#define NEOPIXEL_COUNT 1 // 144
#define JOY_UD 1
#define JOY_LR 0
#define EXP_BTN_0 0
#define EXP_BTN_1 1
#define EXP_BTN_2 2
#define EXP_BTN_3 3
#define EXP_BTN_4 4
#define EXP_BTN_5 5
#define EXP_BTN_6 6
#define EXP_BTN_7 7
#define EXP_GRN_LED 8
#define EXP_RED_LED 9
#define EXP_POWER_PLUG 10
#define EXP_TRIGGER 11
#define EXP_DIMMER 12
#define EXP_VIBE_LEFT 13
#define EXP_VIBE_RIGHT 14
#define EXP_ROTARY_INT 15
#define ROTARY_ADDR 0x36

Adafruit_MCP23X17 mcp;
LightRods lightRods = LightRods(NEOPIXEL_COUNT, NEOPIXEL_PIN);
Joystick joystick = Joystick(JOY_LR, JOY_UD);
FeedbackLEDs feedbackLEDs = FeedbackLEDs(&mcp, EXP_RED_LED, EXP_GRN_LED);
Rotary rotary = Rotary(ROTARY_ADDR);
Screen screen = Screen(TFT_CS, TFT_DC, &mcp, EXP_DIMMER);
MiscIO miscIO = MiscIO(&mcp, EXP_BTN_0, EXP_BTN_1, EXP_BTN_2, EXP_BTN_3,
                       EXP_BTN_4, EXP_BTN_5, EXP_BTN_6, EXP_BTN_7, EXP_TRIGGER,
                       EXP_POWER_PLUG, EXP_ROTARY_INT);
Vibration vibe = Vibration(&mcp, EXP_VIBE_LEFT, EXP_VIBE_RIGHT);
State state = State();
Interrupts interrupts =
    Interrupts(&state, &mcp, &rotary, &miscIO, INTERRUPT_PIN);

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
  miscIO.begin();
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

  joystickValues joystickPos = joystick.sample();
  signed long rotary_pos = rotary.getValue();
  signed long rotary_isPressed = rotary.isPressed();
  bool btn_0_pressed = miscIO.isPressed(miscIO.menu);
  bool btn_1_pressed = miscIO.isPressed(miscIO.up);
  bool btn_2_pressed = miscIO.isPressed(miscIO.record);
  bool btn_3_pressed = miscIO.isPressed(miscIO.left);
  bool btn_4_pressed = miscIO.isPressed(miscIO.down);
  bool btn_5_pressed = miscIO.isPressed(miscIO.right);
  bool btn_6_pressed = miscIO.isPressed(miscIO.one);
  bool btn_7_pressed = miscIO.isPressed(miscIO.two);
  bool trigger_pressed = miscIO.isPressed(miscIO.trigger);
  bool power_plug_grounded = miscIO.isPressed(miscIO.power);

  screen.tmp_display(joystickPos.lr, joystickPos.ud, rotary_pos,
                     rotary_isPressed, btn_0_pressed, btn_1_pressed,
                     btn_2_pressed, btn_3_pressed, btn_4_pressed, btn_5_pressed,
                     btn_6_pressed, btn_7_pressed, power_plug_grounded,
                     trigger_pressed);

  if (btn_0_pressed) {
    if (power_plug_grounded) {
      lightRods.tmp_fill(255, 0, 255);
    } else {
      lightRods.tmp_fill(122, 0, 122);
    }
    delay(150);
    lightRods.off();
  }

  if (btn_1_pressed) {
    feedbackLEDs.on(FEEDBACK_GREEN);
    delay(150);
    feedbackLEDs.off(FEEDBACK_GREEN);
  }

  if (btn_2_pressed) {
    feedbackLEDs.on(FEEDBACK_RED);
    delay(150);
    feedbackLEDs.off(FEEDBACK_RED);
  }

  if (btn_3_pressed) {
    screen.toggleBrightness();
  }

  if (btn_4_pressed) {
    vibe.tmp_vibrate();
  }
}