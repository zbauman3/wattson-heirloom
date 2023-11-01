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
Vibration vibe;
Interrupts interrupts = Interrupts(&state, &mcp, &rotary);

void setup() {

  vibe.begin();

  // ESP32-s2 has different pins for the i2c headers/stemmaQT.
  // We want to use stemmaQT, so we need to set the pins here.
  Wire.setPins(PinDefs::i2cSda, PinDefs::i2cScl);

  DEBUG_INIT(9600);
  DEBUG_LN("Started!");

  if (!mcp.begin_I2C(MCP23XXX_ADDR, &Wire)) {
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

  if (state.mcp_up) {
    feedbackLEDs.flashGreen();
  }

  if (state.mcp_record) {
    feedbackLEDs.flashRed();
  }

  if (state.mcp_left) {
    screen.toggleBrightness();
  }

  if (state.mcp_trigger) {
    lightRods.startPattern(1);
    vibe.startPattern(1);
  }
}