#include "./FeedbackLEDs.h"
#include "./Interrupts.h"
#include "./Joystick.h"
#include "./LightRods.h"
#include "./Macros.h"
#include "./Rotary.h"
#include "./Screen.h"
#include "./State.h"
#include "./Vibration.h"
#include <AceRoutine.h>
#include <Adafruit_MCP23X17.h>

Adafruit_MCP23X17 mcp;
State state;
LightRods lightRods;
Joystick joystick(&state);
FeedbackLEDs feedbackLEDs = FeedbackLEDs(&mcp);
Rotary rotary = Rotary(&state);
Screen screen(&state, &mcp, &joystick);
Vibration vibe(&mcp);
Interrupts interrupts = Interrupts(&state, &mcp, &rotary);

void setup() {
  DEBUG_INIT(9600);
  DEBUG_LN("Started!");

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

  ace_routine::CoroutineScheduler::setup();
}

// TODO move this to the screen
bool firstDraw = true;

void loop(void) {
  ace_routine::CoroutineScheduler::loop();

  interrupts.loop();

  if (!firstDraw && !state.hasInterrupt()) {
    return;
  }

  DEBUG_LN("--Acting--");

  firstDraw = false;

  screen.tmp_display();

  if (state.mcp_menu) {
    lightRods.tmp_flash();
  }

  if (state.mcp_up) {
    feedbackLEDs.flashGreen();
  }

  if (state.mcp_record) {
    feedbackLEDs.flashRed();
  }

  if (state.mcp_left) {
    screen.toggleBrightness();
  }

  if (state.mcp_down) {
    vibe.tmp_vibrate();
  }
}