#include "./src/config/Macros.h"
#include "./src/controllers/Interrupts.h"
#include "./src/controllers/Joystick.h"
#include "./src/controllers/Rotary.h"
#include "./src/feedback/Leds.h"
#include "./src/feedback/LightRods.h"
#include "./src/feedback/Screen.h"
#include "./src/feedback/Vibration.h"
#include "./src/models/State.h"
#include "./src/views/ViewManager.h"
#include <AceRoutine.h>
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

Adafruit_MCP23X17 mcp;
State state;
LightRods lightRods;
Joystick joystick(&state);
Leds leds(&mcp);
Rotary rotary(&state);
Screen screen(&state, &mcp);
Vibration vibration;
Interrupts inter(&state, &mcp, &rotary);
ViewManager viewManager(&state, &screen, &joystick, &leds, &lightRods,
                        &vibration);

void setup() {

  // call immediately to prevent initial Vibration
  // still needed after pulldown resistor?
  vibration.begin();

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
  leds.begin();
  inter.begin();
}

int debugTimer = 0;
uint8_t debugStep = 0;
signed long debugRotaryPos = 0;
signed long debugDistance = 5;

void loop(void) {
  inter.loop();

  leds.loop();
  lightRods.runCoroutine();
  viewManager.loop();
  vibration.runCoroutine();

  // TODO remove this tmp code below
  if (state.hasInterrupt()) {
    if (state.mcp_up) {
      leds.flashGreen();
    }

    if (state.mcp_record) {
      leds.flashRed();
    }

    if (state.mcp_left) {
      screen.toggleBrightness();
    }

    if (state.mcp_trigger) {
      lightRods.startPattern(1);
      vibration.startPattern(1);
    }
  }
}