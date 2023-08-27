#define DEBUG_ENABLED 1

#include "./FeedbackLEDs.h"
#include "./Joystick.h"
#include "./Keypad.h"
#include "./LightRods.h"
#include "./Macros.h"
#include "./Rotary.h"
#include "./Screen.h"
#include <Adafruit_MCP23X17.h>

#define TFT_DC 20
#define TFT_CS 21
// #define INTERRUPT      4
#define NEOPIXEL_PIN 3
#define NEOPIXEL_COUNT 144
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
#define ROTARY_ADDR 0x36

Adafruit_MCP23X17 mcp;
LightRods lightRods = LightRods(NEOPIXEL_COUNT, NEOPIXEL_PIN);
Joystick joystick = Joystick(JOY_LR, JOY_UD);
FeedbackLEDs feedbackLEDs = FeedbackLEDs(&mcp, EXP_RED_LED, EXP_GRN_LED);
Rotary rotary = Rotary(ROTARY_ADDR);
Screen screen = Screen(TFT_CS, TFT_DC, &mcp, EXP_DIMMER);
Keypad keypad = Keypad(&mcp, EXP_BTN_0, EXP_BTN_1, EXP_BTN_2, EXP_BTN_3,
                       EXP_BTN_4, EXP_BTN_5, EXP_BTN_6, EXP_BTN_7);

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
  keypad.begin();
  mcp.pinMode(EXP_POWER_PLUG, INPUT_PULLUP);
  mcp.pinMode(EXP_TRIGGER, INPUT_PULLUP);
}

void loop(void) {

  joystickValues joystickPos = joystick.sample();
  signed long rotary_pos = rotary.getValue();
  bool btn_0_pressed = keypad.isPressed(KEYPAD_MENU);
  bool btn_1_pressed = keypad.isPressed(KEYPAD_UP);
  bool btn_2_pressed = keypad.isPressed(KEYPAD_RECORD);
  bool btn_3_pressed = keypad.isPressed(KEYPAD_LEFT);
  bool btn_4_pressed = keypad.isPressed(KEYPAD_DOWN);
  bool btn_5_pressed = keypad.isPressed(KEYPAD_RIGHT);
  bool btn_6_pressed = keypad.isPressed(KEYPAD_ONE);
  bool btn_7_pressed = keypad.isPressed(KEYPAD_TWO);
  bool power_plug_grounded = !mcp.digitalRead(EXP_POWER_PLUG);
  bool trigger_pressed = !mcp.digitalRead(EXP_TRIGGER);

  screen.tmp_display(joystickPos.lr, joystickPos.ud, rotary_pos, btn_0_pressed,
                     btn_1_pressed, btn_2_pressed, btn_3_pressed, btn_4_pressed,
                     btn_5_pressed, btn_6_pressed, btn_7_pressed,
                     power_plug_grounded, trigger_pressed);

  if (btn_0_pressed) {
    if (power_plug_grounded) {
      lightRods.tmp_fill(255, 0, 255);
    } else {
      lightRods.tmp_fill(122, 0, 122);
    }
  } else {
    lightRods.off();
  }

  if (btn_1_pressed) {
    feedbackLEDs.on(FEEDBACK_GREEN);
  } else {
    feedbackLEDs.off(FEEDBACK_GREEN);
  }

  if (btn_2_pressed) {
    feedbackLEDs.on(FEEDBACK_RED);
  } else {
    feedbackLEDs.off(FEEDBACK_RED);
  }

  if (btn_3_pressed) {
    screen.toggleBrightness();
  }

  delay(10);
}
