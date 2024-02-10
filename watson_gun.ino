#include "./src/config/Macros.h"
#include "./src/controllers/Interrupts.h"
#include "./src/controllers/Joystick.h"
#include "./src/controllers/Rotary.h"
#include "./src/feedback/Leds.h"
#include "./src/feedback/LightRods.h"
#include "./src/feedback/Screen.h"
#include "./src/feedback/Vibration.h"
#include "./src/models/State.h"
#include <AceRoutine.h>
#include <Adafruit_MCP23X17.h>

Adafruit_MCP23X17 mcp;
State state;
LightRods lightRods;
Joystick joystick(&state);
Leds feedbackLEDs = Leds(&mcp);
Rotary rotary = Rotary(&state);
Screen screen(&state, &mcp, &joystick);
Vibration vibe;
Interrupts interrupts = Interrupts(&state, &mcp, &rotary);

void setup() {

  // call immediately to prevent initial Vibration
  // still needed after pulldown resistor?
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
}

void loop(void) {
  interrupts.loop();

  feedbackLEDs.loop();
  lightRods.runCoroutine();
  screen.loop();
  vibe.runCoroutine();

  // TODO remove this tmp code
  if (state.hasInterrupt()) {
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
}