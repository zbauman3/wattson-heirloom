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
State state = State();
LightRods lightRods = LightRods();
Joystick joystick;
FeedbackLEDs feedbackLEDs = FeedbackLEDs(&mcp);
Rotary rotary = Rotary(&state);
Screen screen = Screen(&mcp);
Vibration vibe = Vibration(&mcp);
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

  joystickValues joystickPos = joystick.sample();

  screen.tmp_display(joystickPos.lr, joystickPos.ud, state.rotary_position,
                     state.rotary_btn, state.mcp_menu, state.mcp_up,
                     state.mcp_record, state.mcp_left, state.mcp_down,
                     state.mcp_right, state.mcp_one, state.mcp_two,
                     state.mcp_power, state.mcp_trigger);

  if (state.mcp_menu) {
    if (state.mcp_power) {
      lightRods.tmp_fill(255, 0, 255);
    } else {
      lightRods.tmp_fill(122, 0, 122);
    }
    delay(150);
    lightRods.off();
  }

  if (state.mcp_up) {
    feedbackLEDs.setGreen(HIGH);
    delay(150);
    feedbackLEDs.setGreen(LOW);
  }

  if (state.mcp_record) {
    feedbackLEDs.setRed(HIGH);
    delay(150);
    feedbackLEDs.setRed(LOW);
  }

  if (state.mcp_left) {
    screen.toggleBrightness();
  }

  if (state.mcp_down) {
    vibe.tmp_vibrate();
  }
}